#ifndef STUDENTMAINWINDOW_HH
#define STUDENTMAINWINDOW_HH

#include "actor.hh"
#include "player.hh"
#include "bomb.hh"
#include "core/logic.hh"

#include <iostream>
#include <map>
#include <utility>

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTime>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

namespace Ui {
class StudentMainWindow;
}

namespace StudentSide {
class StudentMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentMainWindow(int time,
                               bool big_background,
                               QWidget *parent = nullptr);
    ~StudentMainWindow();

    void setSize(int w, int h);
    void setPicture(QImage &basic, QImage &big);

    void keyPressEvent(QKeyEvent *event);
    void addPlayer();
    void addBomb();
    void addBombs();
    void setBombVisbility(bool val);
    void addActor(int locX, int locY, int type = 0);
    void addNysse(int x, int y, std::shared_ptr<Interface::IActor> nysse);
    void addPassenger(int x, int y, std::shared_ptr<Interface::IActor> passenger);
    void addStop(int x, int y, std::shared_ptr<Interface::IStop> stop);
    void removeActor(std::shared_ptr<Interface::IActor> actor);
    bool findActorInMap(std::string actortype,std::shared_ptr<Interface::IActor> actor);

    void updateNysseCoordinate(std::shared_ptr<CourseSide::Nysse> nysse);
    void updatePassengerCoordinate(std::shared_ptr<CourseSide::Passenger> passenger);
    void updatePlayerCoords(int dX, int dY);

    CourseSide::Logic *return_logic();
    StudentSide::Player *returnplayer();
    bool returnGameOver();
    bool returnPlayerEat();
    void switchPlayerEat();
    bool isBigMapSelected();

    void startTimer();
    void updateScore();
    void gameOver();

public slots:
    void updateTime();

private:
    Ui::StudentMainWindow *ui;
    QGraphicsScene *map_;
    QTimer *timer_;

    StudentSide::Player *player_;
    StudentSide::Actor *last_;
    QVector<StudentSide::Bomb*> bombs_;
    QVector<QGraphicsItem*> actors_;
    std::map<std::shared_ptr<Interface::IActor>, StudentSide::Actor*> nysses_;
    std::map<std::shared_ptr<Interface::IActor>, StudentSide::Actor*> passengers_;
    std::map<std::shared_ptr<Interface::IStop>, StudentSide::Actor*> stops_;
    std::map<std::shared_ptr<Interface::IActor>, StudentSide::Actor*>::iterator iter_;

    CourseSide::Logic logic_;
    bool bigMapSelected_;
    bool gameOver_;
    bool playerEat_;
    int score_;
    int seconds_;
    double speed_;

    int width_;
    int height_;

    const int STOP_TYPE = 1;
    const int NYSSE_TYPE = 2;
    const int PASSENGER_TYPE = 3;
    const int MAPPADDING = 2;
    const int LCDHEIGHT = 35;
    const int OUTOFMAP = -20;
    const int SPAWNRANGE = 30;
    const int BOMBRANGE = 10;
    const int BOMBNUMBER = 10;
};

} //namespace
#endif // STUDENTMAINWINDOW_HH
