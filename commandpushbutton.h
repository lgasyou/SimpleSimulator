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

	void setCommand(int command) { this->command = command; }

public slots:
	virtual void repeater();

signals:
	void sendCommand(int);

protected:
	int command;
};

#endif // COMMANDPUSHBUTTON_H
