#include "engine.hh"
#include "startdialog.hh"

namespace StudentSide {

Engine::Engine(){
    // dialog to select time and map size
    startDialog *dialogwindow = new startDialog();
    dialogwindow->exec();
    // return play time from dialogwindow
    seconds_ = dialogwindow->return_time_input();
    // return map size from dialogwindow
    big_background_ = dialogwindow->return_dialog_size();
    createGame();
}

void Engine::createGame(){
    QImage BASIC_BACKGROUD(":/offlinedata/offlinedata/kartta_pieni_500x500.png");
    QImage BIG_BACKGROUND(":/offlinedata/offlinedata/kartta_iso_1095x592.png");

    // Create window
    StudentSide::StudentMainWindow* window =
            new StudentSide::StudentMainWindow(seconds_, big_background_);

    // Create city
    city_ = std::make_shared<StudentSide::City>(window);
    city_->setBackground(BASIC_BACKGROUD,BIG_BACKGROUND);
    // Create busses, passengers, stops and make then move
    int randHour = rand() % 15;
    city_->getWindow()->return_logic()->setTime( randHour + 7, 0);
    city_->getWindow()->show();
    city_->getWindow()->return_logic()->readOfflineData(CourseSide::DEFAULT_BUSES_FILE,
                          CourseSide::DEFAULT_STOPS_FILE);
    city_->getWindow()->return_logic()->fileConfig();
    city_->getWindow()->return_logic()->takeCity(city_);
    city_->getWindow()->return_logic()->finalizeGameStart();
    // Create bombs and player
    city_->getWindow()->addBombs();
    city_->getWindow()->addPlayer();
}

} // namespace
