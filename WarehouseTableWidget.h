#ifndef WAREHOUSETABLEWIDGET_H
#define WAREHOUSETABLEWIDGET_H

class Warehouse;
#include <QTableWidget>

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

	void updateDisplay();

	void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

private:
	// transforms double into QString
	QString toString(double value);

	Warehouse *warehouse_;
};

#endif // WAREHOUSETABLEWIDGET_H
