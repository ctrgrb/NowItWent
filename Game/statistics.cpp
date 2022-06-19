#include "statistics.hh"

namespace StudentSide {

Statistics::Statistics(){}

int Statistics::givePoints() const{
    return points_;
}

void Statistics::passengerDied(int num){
    points_ += num*POINTS_PER_PASSENGER;
}

void Statistics::morePassengers(int num){
    passenger_ += num;
}

void Statistics::nysseRemoved(){
    points_ += POINTS_PER_BUS;
}

void Statistics::newNysse(){
    nysses_ += 1;
}

void Statistics::nysseLeft(){
    nysses_ -= 1;
}

void Statistics::clearPoints()
{
    points_ = 0;
}

int Statistics::getPassengers()
{
    return passenger_;
}

int Statistics::getNysses()
{
    return nysses_;
}
}
