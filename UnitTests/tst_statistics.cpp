#include <QtTest>

// add necessary includes here

class statistics : public QObject
{
    Q_OBJECT

public:
    statistics();
    ~statistics();

private slots:
    void test_case1();

};

statistics::statistics()
{

}

statistics::~statistics()
{

}

void statistics::test_case1()
{

}

QTEST_APPLESS_MAIN(statistics)

#include "tst_statistics.moc"
