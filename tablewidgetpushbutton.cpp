#include "tablewidgetpushbutton.h"

TableWidgetPushButton::TableWidgetPushButton(QWidget *parent, int command) :
	CommandPushButton(parent, command) {	
	init();
}

TableWidgetPushButton::TableWidgetPushButton(const QString &text, int command, QWidget *parent) :
	CommandPushButton(text, command, parent) {
	init();
}

void TableWidgetPushButton::repeater() {
	emit sendCommand(this->command(), this->index());
}
