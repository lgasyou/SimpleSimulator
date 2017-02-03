#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>

class BuildingBase;
class Company;
class GarageTableWidget;
class WarehouseTableWidget;
class Industry;
class MyPushButton;
namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent);
    ~BuildingDetailDialog();

    inline void setBuilding(BuildingBase *building) { this->building_ = building; }
    inline void setVisitor(Company *visitor) { this->visitor_ = visitor; }

public slots:
	void updateDisplay();

	void switchIndustryDisplay(bool);

	// Changes the type of building by button's text
	void changeType(MyPushButton *);

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
	void buySignal(BuildingBase *);
	void sellSignal(BuildingBase *);
	void changeTypeSignal(BuildingBase *, const QString &buildingType);
	void manageSignal(BuildingBase *, const QString &cmd);

private slots:
	void on_pushButton_Buy_clicked();
	void on_pushButton_Sell_clicked();

	void on_pushButton_Manage_clicked();
	void on_pushButton_Dismantle_clicked();

	void on_pushButton_Build_clicked();

private:
    BuildingBase *building_;
    Company *visitor_;

	GarageTableWidget *garageTableWidget_;
    WarehouseTableWidget *warehouseTableWidget_;
    Ui::BuildingDetailDialog *ui;
};

#endif // BUILDINGDETAILDIALOG_H
