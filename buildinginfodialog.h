#ifndef BUILDINGINFODIALOG_H
#define BUILDINGINFODIALOG_H

#include <QDialog>

class BaseBuilding;
class Company;
class BaseIndustry;
struct Goods;

class GarageTableWidget;
class WarehouseTableWidget;
class MyPushButton;
namespace Ui {
class BuildingInfoDialog;
}

class BuildingInfoDialog : public QDialog {
    Q_OBJECT

public:
    BuildingInfoDialog(QWidget *parent = nullptr);

    ~BuildingInfoDialog();

	inline void showAndRaise();

    inline void setBuilding(BaseBuilding *building) { this->building_ = building; }

    inline void setVisitor(Company *visitor) { this->visitor_ = visitor; }

public slots:
	void updateDisplay();

	// Changes the type of building by button's text
	void changeType(MyPushButton *);

	// Receives the data comes from WarehouseTableWidget or GarageTableWidget.
	// Send infomation to model BaseIndustry.
	void deliverGoods(const Goods &goods, BaseIndustry *dest);

signals:
	void buySignal(BaseBuilding *);

	void sellSignal(BaseBuilding *);

	void changeTypeSignal(BaseBuilding *, const QString &buildingType);

	void manageSignal(BaseBuilding *, const QString &cmd);

	void dataChanged();

private slots:
	void addNewVihicle();

	void on_pushButton_Buy_clicked();

	void on_pushButton_Sell_clicked();

	void on_pushButton_Dismantle_clicked();

	void on_pushButton_Build_clicked();

private:
	// Hides all variable widget in order to display correctly.
	void hideVariableWidget();

	void displayBasicInfo();

	// Displays according to whether the visitor is owner or not.
	void displayAccordingToVisitor();

	// Displays according to the type of building.
	void typeIsFoundation();
	void typeIsIndustry();
	void typeIsCommerce();
	void typeIsResidence();

	void showGarage(BaseIndustry *);

	void showWarehouse(BaseIndustry *);

	// transforms double into QString
	static QString toString(double value);

private:
    BaseBuilding *building_;

    Company *visitor_;

	GarageTableWidget *garageTableWidget_;

    WarehouseTableWidget *warehouseTableWidget_;

    Ui::BuildingInfoDialog *ui;
};

inline void BuildingInfoDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !BUILDINGINFODIALOG_H
