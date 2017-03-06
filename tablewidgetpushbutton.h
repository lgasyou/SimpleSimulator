#ifndef TABLEWIDGETPUSHBUTTON_H
#define TABLEWIDGETPUSHBUTTON_H

#include <QPushButton>

// This PushButton is specialized to send index of this button in table widget while clicked.
class TableWidgetPushButton : public QPushButton {
    Q_OBJECT

public:
    TableWidgetPushButton(QWidget *parent = nullptr);
    TableWidgetPushButton(const QString &text, QWidget *parent = nullptr);

	void init();

	void setIndex(int index) { this->indexInTable_ = index; }
	int index() const { return this->indexInTable_; }

public slots:
	void repeater();

signals:
    void sendPointer(TableWidgetPushButton *);

private:
	int indexInTable_;
};

#endif // MYPUSHBUTTON_H
