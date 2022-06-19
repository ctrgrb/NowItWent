#include "city.hh"

namespace StudentSide {

City::City(StudentMainWindow *window){
    window_ = window;
}

City::~City(){}

void City::setBackground(QImage &basicbackground, QImage &bigbackground){
    window_->setPicture(basicbackground, bigbackground);
}

void City::addStop(std::shared_ptr<Interface::IStop> stop){
    Interface::Location location = stop->getLocation();
    window_->addStop(location.giveX(),location.giveY(), stop);
}

void City::addActor(std::shared_ptr<Interface::IActor> newactor){
    std::shared_ptr<CourseSide::Nysse> nysse =
            std::dynamic_pointer_cast<CourseSide::Nysse>(newactor);
    std::shared_ptr<CourseSide::Passenger> passenger =
            std::dynamic_pointer_cast<CourseSide::Passenger>(newactor);
    Interface::Location location = newactor->giveLocation();

    // Add busses and passengers in window and store the objects in vectors
    if (nysse != 0){
        nysses_.push_back(nysse);
        window_->addNysse(location.giveX(),location.giveY(), nysse);
    }
    if (passenger != 0){
        passengers_.push_back(passenger);
        window_->addPassenger(location.giveX(),location.giveY(),passenger);
    }
}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const{
    if(actor->isRemoved()){
        return false;
    }
    return true;
}

std::vector<std::shared_ptr<Interface::IActor> >
        City::getNearbyActors(Interface::Location loc) const{

    std::vector<std::shared_ptr<Interface::IActor>> nearActors;
    int DISTANCE = 20;

    // Search for actors in the vicinity of 20 pxls. Store these actors in
    // a vector that is returned by the function
    Interface::Location location;
    for (auto nysse : nysses_){
        location = nysse->giveLocation();
        if (loc.giveX() - DISTANCE < location.giveX() and
                loc.giveX()+DISTANCE > location.giveX() and
                loc.giveY()-DISTANCE < location.giveY() and
                loc.giveY()+DISTANCE > location.giveY()){
            nearActors.push_back(nysse);
        }
    }
    for (auto passenger : passengers_){
        location = passenger->giveLocation();
        if (loc.giveX() - DISTANCE < location.giveX() and
                loc.giveX()+DISTANCE > location.giveX() and
                loc.giveY()-DISTANCE < location.giveY() and
                loc.giveY()+DISTANCE > location.giveY()){
            nearActors.push_back(passenger);
        }
    }
    return nearActors;
}

StudentMainWindow *City::getWindow(){
    return window_;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor){
    // remove actors near player if spacebar is clicked
    if(window_->returnPlayerEat()){
        int playerX = window_->returnplayer()->return_location()[0];
        int playerY = window_->returnplayer()->return_location()[1];

        Interface::Location playerloc;
        playerloc.setXY(playerX,playerY);

        std::vector<std::shared_ptr<Interface::IActor>> actors_near_player =
                getNearbyActors(playerloc);
        // Remove nearby actors
        if (!actors_near_player.empty()){
            for (auto actor : actors_near_player){
                removeActor(actor);
                window_->removeActor(actor);
                window_->updateScore();
            }
        }
        window_->switchPlayerEat();
    }

    // move buses, when this funktion is called with nysse actor
    std::shared_ptr<CourseSide::Nysse> nysse =
            std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
    bool bigMapSelected = window_->isBigMapSelected();

    if(bigMapSelected){
        maxX_ = 1020;
    } else {
        maxX_ = 520;
    }

    if( nysse != 0 and nysse->giveLocation().giveX() <= maxX_ and
            nysse->giveLocation().giveY() <= maxY_ and
            nysse->giveLocation().giveX() >= minX_ and
            nysse->giveLocation().giveY() >= minY_) {

        if (window_->findActorInMap("nysse", actor) == true){
            window_->addNysse(actor->giveLocation().giveX(),
                              actor->giveLocation().giveY(),actor);
        }

    window_->updateNysseCoordinate(nysse);
    }

    // move passengers, when funktion is called with passenger actor
    std::shared_ptr<CourseSide::Passenger> passenger =
            std::dynamic_pointer_cast<CourseSide::Passenger>(actor);

    if (passenger != 0 and passenger->giveLocation().giveX() <= maxX_ and
            passenger->giveLocation().giveY() <= maxY_ and
            passenger->giveLocation().giveX() >= minX_ and
            passenger->giveLocation().giveY() >= minY_){

        if ( window_->findActorInMap("passenger",actor) == true){
            window_->addPassenger(actor->giveLocation().giveX(),
                                  actor->giveLocation().giveY(),actor);
        }

        window_->updatePassengerCoordinate(passenger);
    }

}

bool City::isGameOver() const{
    if(window_->returnGameOver()){
        return true;
    }
    return false;
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor){
    actor->remove();
}

// Unneeded functions from Interface
void City::setClock(QTime clock){}
void City::startGame(){}
void City::actorRemoved(std::shared_ptr<Interface::IActor> actor){}

} // namespace
