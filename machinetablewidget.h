#ifndef MACHINETABLEWIDGET_H
#define MACHINETABLEWIDGET_H

#include <QTableWidget>

class BaseBuilding;
class BaseIndustry;
class Machine;

class MyPushButton;

class MachineTableWidget : public QTableWidget {
	Q_OBJECT

public:
	MachineTableWidget(QWidget *parent = nullptr);

	~MachineTableWidget();

	void init();

	void setIndustry(BaseBuilding *industry);

public slots:
	void receiveShowDetailSignal(MyPushButton *);

	void updateDisplay();

signals:
	void sendSelectedMachine(Machine *);

private:
	BaseIndustry *industry_;
};

#endif // MACHINETABLEWIDGET_H