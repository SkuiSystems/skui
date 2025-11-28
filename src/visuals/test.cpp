#include "test.h"

Test::Test(QWidget *parent, unsigned int uid) : Visual(parent, uid)
{
    setGeometry(QRect(200, 200, 200, 200));
    setMinimumSize(QSize(200, 200));

    info_name = "Test Class";
    info_class_name = "Test";
    info_description = "Basic child to test functionality of the Visual base class.";
    qDebug() << geometry();

    QLabel *button = new QLabel("TEST", this);
    button->show();

    qDebug() << geometry();
}
