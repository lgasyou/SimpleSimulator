#ifndef WAREHOUSETABLEWIDGET_H
#define WAREHOUSETABLEWIDGET_H

#include <QTableWidget>

class Warehouse;
class BaseIndustry;
class BaseBuilding;
struct Goods;

class MyPushButton;
class SelectTableWidget;

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

	void init();

	inline void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

signals:
	void sendPreorder(const Goods &goods, BaseIndustry *dest);

public slots:
	void goSelectIndustry();

	void getGoods(MyPushButton *);

	void getDestAndSendPreorder(BaseBuilding *dest);

	void updateDisplay();

private:
	// transforms double into QString
	static QString toString(double value);

	Warehouse *warehouse_;
	SelectTableWidget *selectTableWidget_;
	Goods *goods_;
};

#endif // WAREHOUSETABLEWIDGET_H
