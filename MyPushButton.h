#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton {
    Q_OBJECT

public:
    MyPushButton();
    MyPushButton(const QString &text);

	inline void setIndex(int index) { this->index_ = index; }

	QPoint getLocation() const;

signals:
    void sendPointer(MyPushButton *);

	void sendLocation(int);

public slots:
    void repeater(bool);

private:
	int index_;
};

#endif // MYPUSHBUTTON_H
