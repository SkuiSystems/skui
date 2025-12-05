#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>

#include "../visual.h"

class Slider : public Visual
{
    Q_OBJECT
public:
    explicit Slider(QWidget *parent = nullptr, unsigned int uid = 0);

protected:
    bool eventFilter(QObject *, QEvent *) override;

private:
    QSlider *m_slider;
};

#endif // SLIDER_H
