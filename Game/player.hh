#ifndef PLAYER_HH
#define PLAYER_HH

#include <QGraphicsItem>
#include <QPainter>

namespace StudentSide {

class Player : public QGraphicsItem{

public:
    Player(int x, int y);
    virtual ~Player();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCoord(int x, int y);
    std::vector<int> return_location();

private:
    int x_;
    int y_;
};
};

#endif // PLAYER_HH
