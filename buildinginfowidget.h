#ifndef BUILDINGINFOWIDGET_H
#define BUILDINGINFOWIDGET_H

#include <QWidget>

class BaseBuilding;
class BuildingDetailDialog;
namespace Ui { class BuildingInfoWidget; }

class QString;
class TableWidgetPushButton;

class BuildingInfoWidget : public QWidget {
	Q_OBJECT

public:
	BuildingInfoWidget(QWidget *parent = nullptr);

	~BuildingInfoWidget();

	void setTarget(BaseBuilding *building);

signals:
	void sendOption(const QString &option, BaseBuilding *building);

public slots:
	void receiveOrder(TableWidgetPushButton *);

	void showBuildingDetail();

	void showBuildingInfo(BaseBuilding *building);

	void updateDisplay();

private:
	BaseBuilding *displayedBuilding_;

	BuildingDetailDialog *detailWidget_;

	Ui::BuildingInfoWidget *ui;
};

#endif // !BUILDINGINFOWIDGET_H
