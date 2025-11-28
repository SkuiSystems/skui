#ifndef SKUIEVENT_H
#define SKUIEVENT_H

#include <QEvent>

#define DEFINE_EVENT(name, id) static const QEvent::Type name = static_cast<QEvent::Type>(id)

class SkuiEvent : public QEvent
{
public:
    static const QEvent::Type name = static_cast<QEvent::Type>(2000);
};

#endif // SKUIEVENT_H
