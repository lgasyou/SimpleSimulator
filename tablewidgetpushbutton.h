#ifndef TABLEWIDGETPUSHBUTTON_H
#define TABLEWIDGETPUSHBUTTON_H

#include "commandpushbutton.h"

// This PushButton is specialized to send index of this button in table widget while clicked.
class TableWidgetPushButton : public CommandPushButton {
    Q_OBJECT

public:
    TableWidgetPushButton(QWidget *parent = nullptr, int command = -1);

    TableWidgetPushButton(const QString &text, int command = -1, QWidget *parent = nullptr);

	void setIndex(int index) { this->indexInTable_ = index; }
	int index() const { return this->indexInTable_; }

public slots:
	void repeater() override;

signals:
	void sendCommand(int command, int index);

    void sendPointer(TableWidgetPushButton *);

private:
	int indexInTable_;
};

#endif // MYPUSHBUTTON_H
