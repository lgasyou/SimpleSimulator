#ifndef GARAGETABLEWIDGET_H
#define GARAGETABLEWIDGET_H

#include <QTableWidget>

class BaseBuilding;
class Garage;
class Truck;

class MyPushButton;

class GarageTableWidget : public QTableWidget {
	Q_OBJECT

public:
	GarageTableWidget(QWidget * parent = 0);

	~GarageTableWidget();

	void init();

	void updateEachLine(int index, Truck *);

	inline void setGarage(Garage *garage) { this->garage_ = garage; }

public slots:
	void updateDisplay();

	void showSetRouteDialog(MyPushButton *);

	void setRoute(BaseBuilding *);

private:
	// transforms double into QString
	static QString toString(double value);

	Garage *garage_;
};

#endif // !GARAGETABLEWIDGET_H
