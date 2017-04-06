#ifndef BUILDINGDETAILDIALOG_H
#define BUILDINGDETAILDIALOG_H

#include <QDialog>

class BaseBuilding;
class Machine;

namespace Ui {
class BuildingDetailDialog;
}

class BuildingDetailDialog : public QDialog {
    Q_OBJECT

public:
    BuildingDetailDialog(QWidget *parent = nullptr);

    ~BuildingDetailDialog();

	void showUp();

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

	void sendCommand(int command, BaseBuilding *building);

private slots:
	void addNewMachine();

	void addNewVihicle();

	void setNextMachineProduct(const QString &);

	void showMachineDetail(Machine *);

	void updateMachineDetail(Machine *);

	void receiveCommand(int);

private:
	// Displays according to the type of building.
	void displayAccordingToBuildingType();

	void signalSlotConfig();

	// transforms double into QString
	static QString toString(double value);

private:
    BaseBuilding *building_;

	Machine *selectMachine_;

    Ui::BuildingDetailDialog *ui;
};

inline void BuildingDetailDialog::showUp() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // !BUILDINGDETAILDIALOG_H
