#ifndef IndustryWAREHOUSETABLEWIDGET_H
#define IndustryWAREHOUSETABLEWIDGET_H

class IndustryWarehouse;
#include <QTableWidget>

class IndustryWarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	IndustryWarehouseTableWidget(QWidget *parent = nullptr, IndustryWarehouse *warehouse = nullptr);

	void updateDisplay();

	void setWarehouse(IndustryWarehouse *warehouse) { this->warehouse_ = warehouse; }

private:
	// transforms double into QString
	QString toString(double value);

	IndustryWarehouse *warehouse_;
};

#endif // IndustryWAREHOUSETABLEWIDGET_H
