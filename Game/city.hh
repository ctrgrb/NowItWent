#ifndef CITY_HH
#define CITY_HH

#include "interfaces/icity.hh"
#include "actors/passenger.hh"
#include "actors/nysse.hh"
#include "actors/stop.hh"
#include "studentmainwindow.hh"
#include "actor.hh"

namespace StudentSide {

class City : public Interface::ICity
{
public:
    City(StudentSide::StudentMainWindow* window);
    ~City();

    // ICity interface
public:
    void setBackground(QImage &basicbackground, QImage &bigbackground) override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    bool isGameOver() const override;
    StudentMainWindow *getWindow();

private:
    std::vector<std::shared_ptr<Interface::IActor>> nysses_;
    std::vector<std::shared_ptr<Interface::IActor>> passengers_;
    StudentSide::StudentMainWindow* window_;
    Player *player_;
    int maxX_ = 520;
    int maxY_ = 520;
    int minX_ = -20;
    int minY_ = -20;

};
}
#endif // CITY_HH

