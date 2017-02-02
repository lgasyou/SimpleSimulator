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

void MyPushButton::repeater(bool) {
	emit sendPointer(this);
}
