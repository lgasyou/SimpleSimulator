#ifndef GARAGETABLEWIDGET_H
#define GARAGETABLEWIDGET_H

#include <QTableWidget>

class Garage;

class GarageTableWidget : public QTableWidget {
	Q_OBJECT

public:
	GarageTableWidget(QWidget * parent = 0);

	~GarageTableWidget();

	void init();

	inline void setGarage(Garage *garage) { this->garage_ = garage; }

public slots:
	void updateDisplay();

private:
	// transforms double into QString
	static QString toString(double value);

	Garage *garage_;
};

#endif // !GARAGETABLEWIDGET_H