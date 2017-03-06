#include "tablewidgetpushbutton.h"

TableWidgetPushButton::TableWidgetPushButton(QWidget *parent) :
    QPushButton(parent) {	
	init();
}

TableWidgetPushButton::TableWidgetPushButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent) {
	init();
}

void TableWidgetPushButton::init() {
	connect(this, SIGNAL(clicked()),
			this, SLOT(repeater()));
}

void TableWidgetPushButton::repeater() {
	emit sendPointer(this);
}
