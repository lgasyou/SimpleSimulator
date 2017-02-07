#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent) :
    QPushButton(parent)
{	
	init();
}

MyPushButton::MyPushButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent)
{
	init();
}

void MyPushButton::init() {
	connect(this, SIGNAL(clicked(bool)),
		this, SLOT(repeater(bool)));
}

void MyPushButton::repeater(bool) {
	emit sendPointer(this);
}
