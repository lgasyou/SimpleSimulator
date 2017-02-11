#ifndef BUILDINGINFOTABLE_H
#define BUILDINGINFOTABLE_H

#include <QTableWidget>

class BuildingManager;
class BaseBuilding;
class Company;

class MyPushButton;

// This class is used for showing information of Buildings.
// Set Company before use it.
class BuildingInfoTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingInfoTableWidget(QWidget *parent = nullptr);

	void init();

	// Those two functions are still in building.
    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);

    void updateDisplay();

	void displayBasicInfo(int index, BaseBuilding *building);

	void displayAccordingToVisitor(int index, BaseBuilding *building);

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
};

#endif // BUILDINGINFOTABLE_H
