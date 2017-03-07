#ifndef COMMANDPUSHBUTTON_H
#define COMMANDPUSHBUTTON_H

#include <QPushButton>

// The PushButton is specialized to send command when clicked.
class CommandPushButton : public QPushButton {
	Q_OBJECT

public:
	CommandPushButton(QWidget *parent = nullptr, int command = -1);

	CommandPushButton(const QString &text, int command = -1, QWidget *parent = nullptr);

	~CommandPushButton();

	void init();

	void setCommand(int command) { this->command_ = command; }
	int command() const { return this->command_; }

public slots:
	virtual void repeater();

signals:
	void sendCommand(int);

private:
	int command_;
};

#endif // COMMANDPUSHBUTTON_H
