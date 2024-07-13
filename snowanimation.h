// snowanimation.h
#ifndef SNOWANIMATION_H
#define SNOWANIMATION_H

#include <QGraphicsItem>

class SnowAnimation : public QGraphicsItem
{
public:
    SnowAnimation();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void advance(int phase) override;
};

#endif // SNOWANIMATION_H
