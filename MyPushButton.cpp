#include "MyPushButton.h"

MyPushButton::MyPushButton() :
    MyPushButton(tr(""))
{ }

MyPushButton::MyPushButton(const QString &text) :
    QPushButton(text)
{
    connect(this, SIGNAL(clicked(bool)),
            this, SLOT(repeater(bool)));
}

QPoint MyPushButton::getLocation() const {
	int x = frameGeometry().x(),
		y = frameGeometry().y();
	return QPoint(x, y);
}

void MyPushButton::repeater(bool) {
    emit sendPointer(this);
}
