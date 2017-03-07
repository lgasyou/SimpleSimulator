#include "commandpushbutton.h"

CommandPushButton::CommandPushButton(QWidget *parent, int command) : 
	QPushButton(parent),
	command_(command) {
	init();
}

CommandPushButton::CommandPushButton(const QString &text, int command, QWidget *parent) :
	QPushButton(text, parent),
	command_(command) {
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
