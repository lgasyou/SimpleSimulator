#ifndef WAREHOUSETABLEWIDGET_H
#define WAREHOUSETABLEWIDGET_H

#include <QTableWidget>

class Warehouse;
class BaseIndustry;
class BaseBuilding;
struct Goods;

class TableWidgetPushButton;
class SelectTableWidget;

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

	void init();

	inline void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

public slots:
	void goSelectIndustry();

	void getGoods(int index);

	void getDestAndSendPreroute(BaseBuilding *dest);

	void updateDisplay();

signals:
	void sendPreroute(const Goods &goods, BaseIndustry *dest);

	void dataChanged();

private:
	// transforms double into QString
	static QString toString(double value);

private:
	Goods *goods_;

	Warehouse *warehouse_;

	SelectTableWidget *selectTableWidget_;
};

#endif // WAREHOUSETABLEWIDGET_H
