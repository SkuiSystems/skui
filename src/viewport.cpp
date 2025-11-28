#include "viewport.h"

Q_DECLARE_LOGGING_CATEGORY(viewport)
Q_LOGGING_CATEGORY(viewport, "VIEWPORT")

Viewport::Viewport(QWidget *parent)
    : QWidget{parent}
{
    setMouseTracking(true);

    rubber_band = new QRubberBand(QRubberBand::Rectangle, this);
}

QList<Visual *> Viewport::visualChildIn(QRect rect)
{
    QList<Visual *> contained_visuals;
    foreach (Visual *visual, findChildren<Visual *>()) {
        if (rect.intersects(visual->geometry())) {
            contained_visuals.append(visual);
        }
    }
    return contained_visuals;
}

Visual *Viewport::visualChildAt(QPoint point)
{
    QList<Visual *> visuals = findChildren<Visual *>();
    QMutableListIterator<Visual *> visual(visuals);

    Visual *top_level_visual = nullptr;

    while (visual.hasNext()) {
        if (visual.next()->geometry().contains(point)) {
            top_level_visual = visual.value();
        }
    }
    return top_level_visual;
}

void Viewport::setMode(DisplayMode display_mode)
{
    this->display_mode = display_mode;
}

void Viewport::triggeredAlign(AlignDirection direction)
{
    QRect bounding_box = calculateMinimumBoundingBox(selected_visuals);

    for (Visual *visual : selected_visuals) {
        alignVisualToBoundingBox(direction, visual, bounding_box);
    }
}

QRect Viewport::calculateMinimumBoundingBox(const QList<Visual *> &visuals)
{
    int top = INT_MAX;
    int left = INT_MAX;
    int bottom = INT_MIN;
    int right = INT_MIN;

    for (const Visual *visual : visuals) {
        QRect rect = visual->geometry();

        top = std::min(top, rect.top());
        left = std::min(left, rect.left());
        bottom = std::max(bottom, rect.bottom());
        right = std::max(right, rect.right());
    }

    return QRect(QPoint(left, top), QPoint(right, bottom));
}

void Viewport::alignVisualToBoundingBox(AlignDirection direction, Visual *target, QRect bounding_box)
{
    QRect new_geometry = target->geometry();

    switch (direction) {
    case AlignDirection::Top:
        new_geometry.moveTop(bounding_box.top());
        break;
    case AlignDirection::Right:
        new_geometry.moveRight(bounding_box.right());
        break;
    case AlignDirection::Bottom:
        new_geometry.moveBottom(bounding_box.bottom());
        break;
    case AlignDirection::Left:
        new_geometry.moveLeft(bounding_box.left());
        break;
    default:
        return;
    }

    target->setGeometry(new_geometry);
}

void Viewport::select(Visual *visual)
{
    visual->resize_bounding_box->show();
    selected_visuals.append(visual);
    qInfo() << QString("Select: IMPLEMENT NAME");
}

void Viewport::deselectAll()
{
    QMutableListIterator<Visual *> visual(selected_visuals);
    while (visual.hasNext()) {
        visual.next()->resize_bounding_box->hide();
        visual.remove();
        qInfo() << QString("Deselect: IMPLEMENT NAME");
    }
}

void Viewport::selectSingle(QPoint positon)
{
    Visual *top_level_visual = visualChildAt(positon);
    if (top_level_visual) {
        bool shift_down = QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ShiftModifier);
        if (!shift_down)
            deselectAll();
        select(top_level_visual);
    }
}

void Viewport::selectMultiple(QList<Visual *> found_visuals)
{
    if (!found_visuals.isEmpty()) {
        foreach (Visual *visual, found_visuals) {
            select(visual);
        }
    }
}

void Viewport::changeGeometryForSelected(DragDirection active_direction, QPointF delta)
{
    foreach (Visual *visual, selected_visuals) {
        visual->changeGeometryByDelta(active_direction, delta);
    }
}

bool Viewport::inMouseWiggleTolerance(QSize size)
{
    if (size.width() > MAX_MOUSE_WIGGLE_TOLERANCE || size.height() > MAX_MOUSE_WIGGLE_TOLERANCE) {
        return false;
    } else {
        return true;
    }
}

// Note: This is NOT the override method mousePressEvent(QMouseEvent *).
// The handling of the events is done by event(QEvent *)
// It serves simular pourpouse to mousePressEvent(QMouseEvent *),
// but includes Child events in Edit Mode.
void Viewport::mousePressChanged(QMouseEvent *event)
{
    if (display_mode == DisplayMode::Edit) {
        origin = event->pos();
        rubber_band->setGeometry(QRect(origin, QSize(1, 1)));
        rubber_band->show();
    }
}

// Note: This is NOT the override method mouseMoveEvent(QMouseEvent *).
// The handling of the events is done by event(QEvent *)
// It serves simular pourpouse to mouseMoveEvent(QMouseEvent *),
// but includes Child events in Edit Mode.
void Viewport::mousePositionChanged(QMouseEvent *event)
{
    if (display_mode == DisplayMode::Edit) {
        rubber_band->setGeometry(QRect(origin, event->pos()).normalized());
    }
}

// Note: This is NOT the override method mouseReleaseEvent(QMouseEvent *).
// The handling of the events is done by event(QEvent *)
// It serves simular pourpouse to mouseReleaseEvent(QMouseEvent *),
// but includes Child events in Edit Mode.
void Viewport::mouseReleaseChanged(QMouseEvent *event)
{
    if (display_mode == DisplayMode::Edit) {
        rubber_band->hide();

        QList<Visual *> found_visuals = visualChildIn(rubber_band->geometry());
        if (found_visuals.isEmpty()) {
            deselectAll();
            return;
        }

        if (inMouseWiggleTolerance(rubber_band->size())) {
            selectSingle(event->pos());
        } else { // selction via rubber band
            selectMultiple(found_visuals);
        }
    }
}

bool Viewport::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseMove:
        mousePositionChanged(static_cast<QMouseEvent *>(event));
        return true;
    case QEvent::MouseButtonPress:
        mousePressChanged(static_cast<QMouseEvent *>(event));
        return true;
    case QEvent::MouseButtonRelease:
        mouseReleaseChanged(static_cast<QMouseEvent *>(event));
        return true;
    default:
        return QWidget::event(event);
    }
}
