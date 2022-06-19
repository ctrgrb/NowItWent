#ifndef BOMB_HH
#define BOMB_HH

#include <QGraphicsItem>
#include <QPainter>

namespace StudentSide {

class Bomb :  public QGraphicsItem
{
public:
    Bomb(int x, int y);
    virtual ~Bomb();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setCoord(int x, int y);
    std::vector<int> return_location();


private:
    int x_;
    int y_;

    const int BOMBSIZE = 25;
};

}
#endif // BOMB_HH
