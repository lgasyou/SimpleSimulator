#ifndef GARAGETABLEWIDGET_H
#define GARAGETABLEWIDGET_H

#include <QTableWidget>

class BaseBuilding;
class Garage;
class Truck;
struct Route;

class MyPushButton;

class GarageTableWidget : public QTableWidget {
	Q_OBJECT

public:
	GarageTableWidget(QWidget * parent = nullptr);

	~GarageTableWidget();

	void init();

	void updateEachLine(int index, Truck *);

	inline void setGarage(Garage *garage) { this->garage_ = garage; }

public slots:
	void updateDisplay();

	void buttonClicked(MyPushButton *);

	void showSetRouteDialog(MyPushButton *);

	void setRoute(Route *);

signals:
	void dataChanged();

private:
	// transforms double into QString
	static QString toString(double value);

private:
	Garage *garage_;

	int selectedTruckId_;
};

#endif // !GARAGETABLEWIDGET_H
