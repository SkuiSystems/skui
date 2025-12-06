#include "nodeeditor_scence.h"

NodeEditorScence::NodeEditorScence(QObject *parent)
    : QGraphicsScene{parent}
{
    setBackgroundBrush(Qt::white);

    NodeGraphicsItem *node = new NodeGraphicsItem();
    node->setPos(100, 100);

    addItem(node);
    //addRect(QRect(100, 1000, 200, 200), QPen(), QBrush(Qt::blue));
}
