#include "player.hh"

namespace StudentSide {

Player::Player(int x, int y):x_(x), y_(y){
    setPos(mapToParent(x_, y_ ));
}

Player::~Player(){}

QRectF Player::boundingRect() const{
    // Return the size of figure
    return QRectF(0, 0, 30, 30);}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget){
    // Draws player image
    QImage PLAYERIMAGE(":/images/images/player.png");
    QRectF bounds = boundingRect();
    painter->drawImage(bounds,PLAYERIMAGE);
}

void Player::setCoord(int x, int y){
    setX(x);
    setY(y);
    x_ = x;
    y_ = y;
}

std::vector<int> Player::return_location(){
    // Return player location as a {x, y} vector
    std::vector<int> location;
    location.push_back(x_);
    location.push_back(y_);
    return location;
}

}
