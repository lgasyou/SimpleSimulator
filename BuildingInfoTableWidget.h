#ifndef BUILDINGINFOTABLE_H
#define BUILDINGINFOTABLE_H

class BuildingManager;
class BuildingBase;
class Company;
class MyPushButton;
#include <QTableWidget>

class BuildingInfoTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingInfoTableWidget(QWidget *parent = 0);

    bool writeFile(const QString &fileName);
    bool readFile(const QString &fileName);

    void updateDisplay();

    void setBuildingManager(BuildingManager *buildingManager) { this->buildingManager_ = buildingManager; }
    void setCompany(Company *company) { this->company_ = company; }

signals:
    void buySignal(BuildingBase *);
    void sellSignal(BuildingBase *);
    void showDetailSignal(BuildingBase *);

private slots:
    void getBuildingAndSendSignal(MyPushButton *button);

private:
	// transforms double into QString
	static QString toString(double value);

	BuildingManager *buildingManager_;
    Company *company_;
};

#endif // BUILDINGINFOTABLE_H
