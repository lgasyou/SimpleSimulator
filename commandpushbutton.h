#ifndef COMMANDPUSHBUTTON_H
#define COMMANDPUSHBUTTON_H

#include <QPushButton>

// The PushButton is specialized to send command when clicked.
class CommandPushButton : public QPushButton {
	Q_OBJECT

public:
	CommandPushButton(QWidget *parent = nullptr);

	CommandPushButton(const QString &text, QWidget *parent = nullptr);

	~CommandPushButton();

	void init();

	void setCommand(int command) { this->command_ = command; }
	int command() const { return this->command_; }

public slots:
	void repeater();

signals:
	void sendCommand(int);

private:
	int command_;
};

#endif // COMMANDPUSHBUTTON_H
