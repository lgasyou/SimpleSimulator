#ifndef TABLEWIDGETPUSHBUTTON_H
#define TABLEWIDGETPUSHBUTTON_H

#include "commandpushbutton.h"

// This PushButton is specialized to send index of this button in table widget while clicked.
class TableWidgetPushButton : public CommandPushButton {
    Q_OBJECT

public:
    TableWidgetPushButton(QWidget *parent = nullptr, int command = -1);

    TableWidgetPushButton(const QString &text, int command = -1, QWidget *parent = nullptr);

	void setIndex(int index) { this->index = index; }

public slots:
	void repeater() override;

signals:
	void sendData(int index, int command);

private:
	int index;
};

#endif // MYPUSHBUTTON_H
