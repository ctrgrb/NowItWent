#include "bomb.hh"

namespace StudentSide {

Bomb::Bomb(int x, int y):x_(x), y_(y){
    setPos(mapToParent(x_, y_ ));
}

Bomb::~Bomb(){}

QRectF Bomb::boundingRect() const{
    // Return the size of figure
    return QRectF(0, 0, BOMBSIZE, BOMBSIZE);}

void Bomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget){
    // Draws bomb image
    QImage BOMBIMAGE(":/images/images/bomb.png");
    QRectF bounds = boundingRect();
    painter->drawImage(bounds,BOMBIMAGE);
}

void Bomb::setCoord(int x, int y){
    setX(x);
    setY(y);
}

std::vector<int> Bomb::return_location(){
    // Return bomb location as a {x, y} vector
    std::vector<int> location;
    location.push_back(x_);
    location.push_back(y_);
    return location;
}
}
