#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

// This PushButton cooperates with TableWidget.
// It's easier to get index of item than before.
class MyPushButton : public QPushButton {
    Q_OBJECT

public:
    MyPushButton(QWidget *parent = nullptr);
    MyPushButton(const QString &text, QWidget *parent = nullptr);

	void init();

	inline void setIndex(int index) { this->index_ = index; }
	inline int index() const { return this->index_; }

public slots:
	void repeater(bool);

signals:
    void sendPointer(MyPushButton *);

private:
	int index_;
};

#endif // MYPUSHBUTTON_H
