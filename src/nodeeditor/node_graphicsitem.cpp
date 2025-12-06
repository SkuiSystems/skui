#include "node_graphicsitem.h"

NodeGraphicsItem::NodeGraphicsItem(QGraphicsItem *parent)
    : QGraphicsItem{parent}
{}

void NodeGraphicsItem::paint(QPainter *painter,
                             const QStyleOptionGraphicsItem *option,
                             QWidget *widget)
{
    painter->setPen(QColorConstants::DarkRed);
    painter->setFont(painter->font());
    //painter->drawRect(0, 0, 200, 200);
    painter->drawRect(0, 0, 100, 200);
    painter->drawText(50, 50, "Hallo");
}

QRectF NodeGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, 800, 800);
}