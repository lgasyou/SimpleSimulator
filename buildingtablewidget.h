#ifndef BUILDINGINFOLIST_H
#define BUILDINGINFOLIST_H

#include <QTableWidget>

class BaseBuilding;

// This class is used for showing information of Buildings.
// Set Company before use it.
class BuildingTableWidget : public QTableWidget {
    Q_OBJECT

public:
    BuildingTableWidget(QWidget *parent = nullptr);

	void init();

    void updateDisplay();

	void displayBasicInfo(int index);

	void displayAccordingToVisitor(int index);

signals:
	void sendCommand(int command, BaseBuilding *building);

private slots:
	// Gets command and index of building,
	// sends command and pointer of building.
	void receiveCommand(int command, int index);


private:
	// transforms double into QString
	static QString toString(double value);
};

#endif // BUILDINGINFOLIST_H
