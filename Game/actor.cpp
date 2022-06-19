#include "actor.hh"

namespace StudentSide {

Actor::Actor(int x, int y, int type):x_(x), y_(y), type_(type){
    setPos(mapToParent(x_, y_ ));
}

Actor::~Actor(){}

QRectF Actor::boundingRect() const{
    // Return the size of figure based on the actor type
    if (type_ == 1){
        return QRectF(0, 0, STOPSIZE, STOPSIZE);}
    else if (type_ == 2){
        return QRectF(0, 0, BUSSIZE, BUSSIZE);}
    // ELSE IF type_ == 3:
    return QRectF(0, 0, PASSENGERSIZE, PASSENGERSIZE);
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget){
    // Draws image based on actor type
    if (type_ == 1){
        QImage STOPIMAGE(":/images/images/busstop.png");
        QRectF bounds = boundingRect();
        painter->drawImage(bounds, STOPIMAGE);
    } else if (type_ == 2){
        QImage BUSIMAGE(":/images/images/bus.png");
        QRectF bounds = boundingRect();
        painter->drawImage(bounds, BUSIMAGE);
    } else if (type_ == 3){
        QImage PASSENGERIMAGE(":/images/images/passenger.png");
        QRectF bounds = boundingRect();
        painter->drawImage(bounds, PASSENGERIMAGE);
    }
}

void Actor::setCoord(int x, int y) {
    setX( x );
    setY( y );
}
}
