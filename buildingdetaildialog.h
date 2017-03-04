#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>

class BaseBuilding;
class Company;
class BaseIndustry;
struct Goods;

class WarehouseTableWidget;
class MyPushButton;
namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent = nullptr);

    ~BuildingDetailDialog();

	inline void showAndRaise();

    inline void setBuilding(BaseBuilding *building) { this->building_ = building; }

public slots:
	// Changes the type of building by button's text
	void changeType(MyPushButton *);

	void updateDisplay();

	// Receives the data comes from WarehouseTableWidget or GarageTableWidget.
	// Send infomation to model BaseIndustry.
	//void deliverGoods(const Goods &goods, BaseIndustry *dest);

signals:
	void changeTypeSignal(BaseBuilding *, const QString &buildingType);

	void dataChanged();

	void sendOption(const QString &option, BaseBuilding *building);

private slots:
	//void addNewVihicle();

	void addNewMachine(MyPushButton *);

	void receiveOrder(MyPushButton *);

private:
	// Hides all variable widget in order to display correctly.
	void hideVariableWidget();

	void displayBasicInfo();

	// Displays according to whether the visitor is owner or not.
	void displayAccordingToVisitor();

	//// Displays according to the type of building.
	//void typeIsFoundation();
	//void typeIsIndustry();
	//void typeIsCommerce();
	//void typeIsResidence();

	//void showGarage(BaseIndustry *);

	//void showWarehouse(BaseIndustry *);

	// transforms double into QString
	static QString toString(double value);

private:
    BaseBuilding *building_;

    WarehouseTableWidget *warehouseTableWidget_;

    Ui::BuildingDetailDialog *ui;
};

inline void BuildingDetailDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !BUILDINGDETAILDIALOG_H
