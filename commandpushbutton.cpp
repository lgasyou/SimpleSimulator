#include "commandpushbutton.h"

CommandPushButton::CommandPushButton(QWidget *parent) : 
	QPushButton(parent) {
	init();
}

CommandPushButton::CommandPushButton(const QString &text, QWidget *parent) :
	QPushButton(text, parent) {
	init();
}

CommandPushButton::~CommandPushButton() { }

void CommandPushButton::init() {
	connect(this, SIGNAL(clicked()),
		this, SLOT(repeater()));
}

void CommandPushButton::repeater() {
	emit sendCommand(command_);
}
