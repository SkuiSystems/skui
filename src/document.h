#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QJsonObject>
#include <QObject>

#include "viewport.h"
#include "visual.h"
#include "visuals/test.h"

#include "outbound.h"

class Document : QObject
{
    Q_OBJECT

public:
    Document(Viewport *);
    ~Document();

    QJsonObject save();
    void load(QJsonObject);

    Visual *createVisual(VisualType type);

    DisplayMode display_mode = DisplayMode::Run;

private:
    unsigned int visual_uid_count = 0;
    QList<VisualContainer> visuals;
    QList<Outbound> outbounds;

    Viewport *viewport;
};

#endif // DOCUMENT_H
