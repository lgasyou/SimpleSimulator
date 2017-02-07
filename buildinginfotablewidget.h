#ifndef BUILDINGINFOTABLE_H
#define BUILDINGINFOTABLE_H

#include <QTableWidget>

class BuildingManager;
class BaseBuilding;
class Company;
class MyPushButton;

// This class is used for showing information of Buildings.
// Set buildingManager and Company before using it.
class BuildingInfoTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingInfoTableWidget(QWidget *parent = 0);

	void init();

	// Those two functions are still in building.
    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);

    void updateDisplay();
	void displayBasicInfo(int index, BaseBuilding *building);
	void displayAccordingToVisitor(int index, BaseBuilding *building);

    inline void setCompany(Company *company) { this->company_ = company; }

signals:
    void buySignal(BaseBuilding *);
    void sellSignal(BaseBuilding *);
    void showDetailSignal(BaseBuilding *);

private slots:
	// Gets building by push button and sends 
	// signals according to text of button.
    void getBuildingAndSendSignal(MyPushButton *);

private:
	// transforms double into QString
	static QString toString(double value);

    Company *company_;
};

#endif // BUILDINGINFOTABLE_H
