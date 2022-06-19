#ifndef ACTOR_HH
#define ACTOR_HH

#include <QGraphicsItem>
#include <QPainter>

namespace StudentSide {

const int WIDTH = 10;
const int HEIGHT = 10;

class Actor :  public QGraphicsItem
{
public:
    Actor(int x, int y, int type = 0);
    virtual ~Actor();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setCoord(int x, int y);

private:
    int x_;
    int y_;
    int type_;

    const int STOPSIZE = 25;
    const int BUSSIZE = 35;
    const int PASSENGERSIZE = 25;
};

}

#endif // ACTOR_HH
