#ifndef BUILDINGINFOWIDGET_H
#define BUILDINGINFOWIDGET_H

#include <QWidget>

class BaseBuilding;
namespace Ui { 
class BuildingInfoWidget; 
}

class QString;

class BuildingInfoWidget : public QWidget {
	Q_OBJECT

public:
	BuildingInfoWidget(QWidget *parent = nullptr);

	~BuildingInfoWidget();

	void setTarget(BaseBuilding *building);

signals:
	void sendCommand(int command, BaseBuilding *building);

public slots:
	void receiveCommand(int);

	void showBuildingInfo(BaseBuilding *building);

	void updateDisplay();

private:
	BaseBuilding *displayedBuilding_;

	Ui::BuildingInfoWidget *ui;
};

#endif // !BUILDINGINFOWIDGET_H
