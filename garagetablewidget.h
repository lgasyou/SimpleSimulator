#ifndef GARAGETABLEWIDGET_H
#define GARAGETABLEWIDGET_H

#include <QTableWidget>

class BaseBuilding;
class Garage;
class Truck;
struct Route;

class TableWidgetPushButton;

class GarageTableWidget : public QTableWidget {
	Q_OBJECT

public:
	GarageTableWidget(QWidget * parent = nullptr);

	~GarageTableWidget();

	void init();

	void updateEachRow(int index, Truck *);

	void setGarage(BaseBuilding *garage);

public slots:
	void updateDisplay();

	void buttonClicked(TableWidgetPushButton *);

	void showSetRouteDialog(TableWidgetPushButton *);

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
