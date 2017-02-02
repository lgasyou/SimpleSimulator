#ifndef BUILDINGINFOTABLE_H
#define BUILDINGINFOTABLE_H

#include <QTableWidget>

class BuildingManager;
class BuildingBase;
class Company;
class MyPushButton;

class BuildingInfoTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingInfoTableWidget(QWidget *parent = 0);

	void init();

    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);

    void updateDisplay();
	void displayBasicInfo(int index, BuildingBase *building);
	void displayAccordingToVisitor(int index, BuildingBase *building);

    inline void setBuildingManager(BuildingManager *buildingManager) { this->buildingManager_ = buildingManager; }
    inline void setCompany(Company *company) { this->company_ = company; }

signals:
    void buySignal(BuildingBase *);
    void sellSignal(BuildingBase *);
    void showDetailSignal(BuildingBase *);

private slots:
    void getBuildingAndSendSignal(MyPushButton *);

private:
	// transforms double into QString
	static QString toString(double value);

	BuildingManager *buildingManager_;
    Company *company_;
};

#endif // BUILDINGINFOTABLE_H
