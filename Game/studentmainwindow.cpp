#include "studentmainwindow.hh"
#include "ui_studentmainwindow.h"
#include "statistics.hh"

namespace StudentSide {

StudentMainWindow::StudentMainWindow(int time, bool big_background,
                                     QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::StudentMainWindow)
{
    // Setup initial values
    score_ = 0;
    playerEat_= false;
    gameOver_ = false;
    speed_ = 2;
    seconds_ = time;

    // Set map size
    bigMapSelected_ = big_background;
    if (bigMapSelected_){
        setSize(1095, 592);
    }else{
        setSize(500, 500);
    }

    // Draw map
    ui->setupUi(this);
    ui->centralwidget->setFixedSize(width_,height_);
    ui->graphicsView->setGeometry(0, LCDHEIGHT, width_ + MAPPADDING,
                                  height_ + MAPPADDING);
    map_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(map_);
    map_->setSceneRect(0,0,width_,height_);
    resize(minimumSizeHint());

    // Start timer
    startTimer();
}

StudentMainWindow::~StudentMainWindow(){
    delete ui;}

CourseSide::Logic *StudentMainWindow::return_logic(){
    return &logic_;}

StudentSide::Player *StudentMainWindow::returnplayer(){
    return player_;}

bool StudentMainWindow::isBigMapSelected(){
    return bigMapSelected_;}

bool StudentMainWindow::returnPlayerEat(){
    return playerEat_;}

bool StudentMainWindow::returnGameOver(){
    return gameOver_;}

void StudentMainWindow::switchPlayerEat(){
    playerEat_ = false;}

void StudentMainWindow::setPicture(QImage &basic, QImage &big){
    if (bigMapSelected_){
        map_->setBackgroundBrush(big);
    }else{
         map_->setBackgroundBrush(basic);
    }
}

void StudentMainWindow::addBombs(){
    // Add bombs based on map size
    int bomb_number;
    if (bigMapSelected_){
        bomb_number = 2*BOMBNUMBER;
    }else{
        bomb_number = BOMBNUMBER;}
    for (int i = 0; i < bomb_number; i++){
        addBomb();}
}

void StudentMainWindow::setBombVisbility(bool val){
    for(auto bomb : bombs_){
        bomb->setVisible(val);
    }
}

void StudentMainWindow::updatePlayerCoords(int dX, int dY){
    int curX = player_->return_location()[0];
    int curY = player_->return_location()[1];
    if ( (curX <= OUTOFMAP)|(curX >= width_)
         |(curY <= OUTOFMAP)|(curY >= height_+OUTOFMAP*2) ){
            gameOver();
    }
    // End game if player is near a bomb
    for(auto bomb : bombs_){
        if ( abs(curX - bomb->return_location()[0]) < BOMBRANGE and
             abs(curY - bomb->return_location()[1]) < BOMBRANGE) {
                gameOver();
        }
    }
    player_->moveBy(dX,dY);
    player_->setCoord(curX+dX,curY+dY);
}

void StudentMainWindow::keyPressEvent(QKeyEvent *event){
    // Move with W A S D. Eat with Spacebar
    if (event->key() == Qt::Key_W){
        updatePlayerCoords(0,-speed_);
    }else if(event->key() == Qt::Key_A){
        updatePlayerCoords(-speed_,0);
    }else if(event->key() == Qt::Key_S){
        updatePlayerCoords(0, speed_);
    }else if(event->key() == Qt::Key_D){
        updatePlayerCoords(speed_, 0);
    }else if(event->key() == Qt::Key_Space){
        playerEat_ = true;
    }
}

void StudentMainWindow::addActor(int locX, int locY, int type){
    StudentSide::Actor* nActor = new StudentSide::Actor(locX, locY, type);
    actors_.push_back(nActor);
    map_->addItem(nActor);
    last_ = nActor;
}

void StudentMainWindow::startTimer(){
    timer_ = new QTimer(this);
    connect(timer_, SIGNAL(timeout()), this, SLOT(updateTime()));
    qDebug() << "Time selected: " << seconds_ << " seconds";
    timer_->start(1000);
    ui->LCDseconds->display(seconds_ % 60);
    ui->LCDminutes->display(seconds_ / 60);
}

void StudentMainWindow::setSize(int w, int h){
    width_ = w;
    height_ = h;
}

void StudentMainWindow::addPlayer(){
    // Spawn the player in a random place
    int randX = rand() % (width_-SPAWNRANGE);
    int randY = rand() % (height_-SPAWNRANGE);
    qDebug() << "player spawn x:" << randX;
    qDebug() << "player spawn y:" << randY;
    player_ = new StudentSide::Player(randX,randY);
    map_->addItem(player_);
}


void StudentMainWindow::addBomb(){
    // Spawn a bomb in a random place
    int randX = rand() % (width_-SPAWNRANGE);
    int randY = rand() % (height_-SPAWNRANGE);
    StudentSide::Bomb* nBomb = new StudentSide::Bomb(randX,randY);
    bombs_.push_back(nBomb);
    map_->addItem(nBomb);
    qDebug() << "bomb spawned";
}

void StudentMainWindow::removeActor(std::shared_ptr<Interface::IActor> actor){
    // Remove actors when player eats and add score
    iter_ = nysses_.find(actor);
    if(iter_ != nysses_.end()){
        map_->removeItem(iter_->second);
        score_ += POINTS_PER_BUS;
    }
    iter_ = passengers_.find(actor);
    if(iter_ != passengers_.end()){
        map_->removeItem(iter_->second);
        score_ += POINTS_PER_PASSENGER;
    }
}

bool StudentMainWindow::findActorInMap(std::string actortype,
                                       std::shared_ptr<Interface::IActor> actor){
    if(actortype == "nysse"){
        iter_ = nysses_.find(actor);
        if(iter_ == nysses_.end()){
            return false;}
    } else if (actortype == "passenger"){
        iter_ = passengers_.find(actor);
        if(iter_ == passengers_.end()){
            return false;}
    }
    return true;
}

void StudentMainWindow::addStop(int x, int y,
                                std::shared_ptr<Interface::IStop> stop){
    std::map<std::shared_ptr<Interface::IStop>,
            StudentSide::Actor*>::iterator iter;
    iter = stops_.find(stop);

    if (iter == stops_.end()){
        addActor(x,y,STOP_TYPE);
        stops_[stop] = last_;
    }
}

void StudentMainWindow::addNysse(int x, int y,
                                 std::shared_ptr<Interface::IActor> nysse){
    iter_ = nysses_.find(nysse);
    if (iter_ == nysses_.end()){
        addActor(x,y,NYSSE_TYPE);
        nysses_[nysse] = last_;
    }
}

void StudentMainWindow::addPassenger(int x, int y,
                                     std::shared_ptr<Interface::IActor> passenger){
    iter_ = passengers_.find(passenger);
    if (iter_ == passengers_.end()){
        addActor(x,y,PASSENGER_TYPE);
        passengers_[passenger] = last_;
    }
}

void StudentMainWindow::updateNysseCoordinate(
        std::shared_ptr<CourseSide::Nysse> nysse){
    nysses_.at(nysse)->setCoord(nysse->giveLocation().giveX(),
                                nysse->giveLocation().giveY());
}

void StudentMainWindow::updatePassengerCoordinate(
        std::shared_ptr<CourseSide::Passenger> passenger){
    passengers_.at(passenger)->setCoord(passenger->giveLocation().giveX(),
                                        passenger->giveLocation().giveY());
}

void StudentMainWindow::updateScore(){
    ui->LCDscore->display(score_);
}

void StudentMainWindow::updateTime(){
    // Update time on LCD panels every second
    seconds_ -= 1;
    ui->LCDseconds->display(seconds_ % 60);
    ui->LCDminutes->display(seconds_ / 60);

    // Hide and display bombs every 10 seconds
    if (seconds_ % 10 == 9){
        setBombVisbility(false);
    }
    if (seconds_ % 10 == 0){
        setBombVisbility(true);
    }

    if (seconds_ <= 0) {
        gameOver();
    }
}

void StudentMainWindow::gameOver(){
    timer_->stop();
    player_->setEnabled(false);
    speed_ = 0;
    gameOver_ = true;
    ui->status_label->setText("Game Over!");
    setBombVisbility(true);
}

} // namespace
