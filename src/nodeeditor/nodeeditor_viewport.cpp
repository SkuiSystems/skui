#include "nodeeditor_viewport.h"

NodeEditorViewPort::NodeEditorViewPort(QWidget *parent)
    : QGraphicsView{parent}
{
    setScene(new NodeEditorScence(parent));
    setSceneRect(0, 0, 1000, 1000);
    centerOn(0, 0);

    //setDragMode(DragMode::ScrollHandDrag);
    setResizeAnchor(ViewportAnchor::AnchorUnderMouse);
}