#include <QtTest>
#include <QString>

#include "../Game/statistics.hh"

// add necessary includes here

class UnitTest : public QObject
{
    Q_OBJECT

public:
    UnitTest();
    ~UnitTest();

private slots:
    void clearAndGivePoints();
    void passengerDied();
    void morePassenger();
    void nysseRemoved();
    void addAndRemoveNysses();

};

UnitTest::UnitTest()
{

}

UnitTest::~UnitTest()
{

}

void UnitTest::clearAndGivePoints()
{

    //tests giving and clearing points in stats
    StudentSide::Statistics stats;
    stats.clearPoints();
    stats.passengerDied(10);
    QCOMPARE(stats.givePoints(),10*3);
    stats.clearPoints();
    QCOMPARE(stats.givePoints(),0i);
}

void UnitTest::passengerDied()
{
    StudentSide::Statistics stats;
    int firstPoints = stats.givePoints();
    stats.passengerDied(5);
    int secondPoints = stats.givePoints();
    QCOMPARE(secondPoints-firstPoints, 5*3);
}

void UnitTest::morePassenger()
{
    StudentSide::Statistics stats;
    int pasFirst = stats.getPassengers();
    stats.morePassengers(5);
    int pasLast = stats.getPassengers();
    QCOMPARE(pasLast-pasFirst, 5);
}

void UnitTest::nysseRemoved()
{
    StudentSide::Statistics stats;
    stats.clearPoints();
    stats.nysseRemoved();
    QCOMPARE(stats.givePoints(),50);
}

void UnitTest::addAndRemoveNysses()
{
    StudentSide::Statistics stats;
    int firstNysses = stats.getNysses();
    stats.newNysse();
    stats.newNysse();
    QCOMPARE(stats.getNysses()-firstNysses, 2);
    stats.nysseLeft();
    stats.nysseLeft();
    QCOMPARE(stats.getNysses(),firstNysses);
}



QTEST_APPLESS_MAIN(UnitTest)

#include "tst_unittest.moc"
