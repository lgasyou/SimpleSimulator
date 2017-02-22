#ifndef BUILDINGINFOLIST_H
#define BUILDINGINFOLIST_H

#include <QTableWidget>

class BuildingManager;
class BaseBuilding;
class Company;

class MyPushButton;

// This class is used for showing information of Buildings.
// Set Company before use it.
class BuildingInfoList : public QTableWidget {
    Q_OBJECT

public:
    BuildingInfoList(QWidget *parent = nullptr);

	void init();

    void updateDisplay();

	void displayBasicInfo(int index);

	void displayAccordingToVisitor(int index);

signals:
	void sendOption(const QString &, BaseBuilding *);

private slots:
	// Gets building by push button and sends 
	// signals according to text of button.
    void getBuildingAndSendSignal(MyPushButton *);

private:
	// transforms double into QString
	static QString toString(double value);
};

#endif // BUILDINGINFOLIST_H
