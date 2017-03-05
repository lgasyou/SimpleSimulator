#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>

class BaseBuilding;
class Machine;

class MyPushButton;
namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent = nullptr);

    ~BuildingDetailDialog();

	void showAndRaise();

    void setBuilding(BaseBuilding *building) { this->building_ = building; }

public slots:
	void updateDisplay();

	// Receives the data comes from WarehouseTableWidget or GarageTableWidget.
	// Send information to model BaseIndustry.
	//void deliverGoods(const Goods &goods, BaseIndustry *dest);

protected:
	void closeEvent(QCloseEvent *) override;

signals:
	void dataChanged();

	void sendOption(const QString &option, BaseBuilding *building);

private slots:
	void addNewVihicle(MyPushButton *);

	void addNewMachine(MyPushButton *);

	void setNextMachineProduct(const QString &);

	void showMachineDetail(Machine *);

	void updateMachineDetail(Machine *);

	void receiveOrder(MyPushButton *);

private:
	// Displays according to whether the visitor is owner or not.
	void displayAccordingToVisitor();

	void signalSlotConfig();

	// transforms double into QString
	static QString toString(double value);

private:
    BaseBuilding *building_;

	Machine *selectMachine_;

    Ui::BuildingDetailDialog *ui;
};

inline void BuildingDetailDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !BUILDINGDETAILDIALOG_H
