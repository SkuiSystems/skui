#ifndef NODE_GRAPHICSITEM_H
#define NODE_GRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QPen>
#include <QPointF>

class NodeGraphicsItem : public QGraphicsItem
{
public:
    explicit NodeGraphicsItem(QGraphicsItem *parent = nullptr);

    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;
};

#endif // NODE_GRAPHICSITEM_H