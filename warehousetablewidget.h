#ifndef WAREHOUSETABLEWIDGET_H
#define WAREHOUSETABLEWIDGET_H

#include <QTableWidget>

class Warehouse;
class BaseIndustry;
struct Goods;

class MyPushButton;
class SelectIndustryDialog;

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
	WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

	void init();

	inline void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

signals:
	void sendPreorder(const Goods &goods, BaseIndustry *dest);

public slots:
	void goSelectBaseIndustry();

	void getGoods(MyPushButton *);

	void getDestAndSendSignal(MyPushButton *);

	void updateDisplay();

private:
	// transforms double into QString
	static QString toString(double value);

	Warehouse *warehouse_;
	SelectIndustryDialog *selectBaseIndustryDialog_;
	Goods *goods_;
};

#endif // WAREHOUSETABLEWIDGET_H
