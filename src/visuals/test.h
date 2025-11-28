#ifndef TEST_H
#define TEST_H

#include <QLabel>

#include "../visual.h"

class Test : public Visual
{
    Q_OBJECT
public:
    explicit Test(QWidget *parent = nullptr, unsigned int uid = 0);

};

#endif // TEST_H
