#pragma once
#include <QTableWidget>
class Garage;

class GarageTableWidget : public QTableWidget {
	Q_OBJECT

public:
	GarageTableWidget(QWidget * parent = 0);

	~GarageTableWidget();

	void init();

	void updateDisplay();

	void setGarage(Garage *garage) { this->garage_ = garage; }

private:
	Garage *garage_;
};
