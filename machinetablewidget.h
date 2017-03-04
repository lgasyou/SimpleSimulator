#ifndef MACHINETABLEWIDGET_H
#define MACHINETABLEWIDGET_H

#include <QTableWidget>

class BaseBuilding;
class BaseIndustry;
class Machine;

class MachineTableWidget : public QTableWidget {
	Q_OBJECT

public:
	MachineTableWidget(QWidget *parent = nullptr);

	~MachineTableWidget();

	void init();

	void setIndustry(BaseBuilding *industry);

public slots:
	void updateDisplay();

private:
	BaseIndustry *industry_;
};

#endif // MACHINETABLEWIDGET_H