#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton {
    Q_OBJECT

public:
    MyPushButton();
    MyPushButton(const QString &text);

signals:
    void sendPointer(MyPushButton *);

public slots:
    void repeater(bool);
};

#endif // MYPUSHBUTTON_H
