#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>
#include "goods.h"

class BaseBuilding;
class Company;
class Industry;
class GarageTableWidget;
class WarehouseTableWidget;
struct Goods;
class MyPushButton;
namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent = nullptr);
    ~BuildingDetailDialog();

    inline void setBuilding(BaseBuilding *building) { this->building_ = building; }
    inline void setVisitor(Company *visitor) { this->visitor_ = visitor; }

public slots:
	void updateDisplay();

	void switchIndustryDisplay(bool);

	// Changes the type of building by button's text
	void changeType(MyPushButton *);

	void deliverGoods(const Goods &goods, Industry *dest);

private:
	void hideVariableWidget();
	void displayBasicInfo();
	void displayAccordingToVisitor();

	void typeIsFoundation();
	void typeIsIndustry();
	void typeIsCommerce();
	void typeIsResidence();

	void showGarage(Industry *);
	void showWarehouse(Industry *);

	// transforms double into QString
	static QString toString(double value);

signals:
	void buySignal(BaseBuilding *);
	void sellSignal(BaseBuilding *);
	void changeTypeSignal(BaseBuilding *, const QString &buildingType);
	void manageSignal(BaseBuilding *, const QString &cmd);
	void dataChanged();

private slots:
	void on_pushButton_Buy_clicked();
	void on_pushButton_Sell_clicked();

	void on_pushButton_Dismantle_clicked();

	void on_pushButton_Build_clicked();

private:
    BaseBuilding *building_;
    Company *visitor_;

	GarageTableWidget *garageTableWidget_;
    WarehouseTableWidget *warehouseTableWidget_;
    Ui::BuildingDetailDialog *ui;
};

#endif // BUILDINGDETAILDIALOG_H
