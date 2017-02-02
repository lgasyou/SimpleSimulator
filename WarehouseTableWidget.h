#ifndef WAREHOUSETABLEWIDGET_H
#define WAREHOUSETABLEWIDGET_H

#include <QTableWidget>

class Warehouse;
class MyPushButton;

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

	void init();

	void updateDisplay();

	inline void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

	void sendSignal(MyPushButton *);

private:
	// transforms double into QString
	static QString toString(double value);

	Warehouse *warehouse_;
};

#endif // WAREHOUSETABLEWIDGET_H
