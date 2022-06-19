#ifndef STATISTICS_HH
#define STATISTICS_HH

#include <assert.h>
#include "interfaces/istatistics.hh"

namespace StudentSide {

const int POINTS_PER_PASSENGER = 3;
const int POINTS_PER_BUS = 50;

class Statistics : public Interface::IStatistics
{
public:
    Statistics();

    // IStatistics interface
public:
    virtual int givePoints() const;
    virtual void passengerDied(int num);
    virtual void morePassengers(int num) override;
    virtual void nysseRemoved() override;
    virtual void newNysse() override;
    virtual void nysseLeft() override;
    void clearPoints();
    int getPassengers();
    int getNysses();

private:
    int passenger_ = 0;
    int points_ = 0;
    int nysses_ = 0;
};
}

#endif // STATISTICS_HH
