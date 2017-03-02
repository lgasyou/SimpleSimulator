#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class BaseBuilding;

class MyPushButton;
class BuildingDetailDialog;
class BuildingInfoList;
class BuildingInfoWidget;
class CompanyDetailDialog;
class HelpDialog;
class MainUI;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void init();

signals:
    void dataChanged();

	void sendSelectedBuilding(BaseBuilding *);

private slots:
	// Opens bank dialog.
    void goBank();

	// Calls function update() of every variable objects.
    void endTurns();

	void showBuildingInfoList();

    void showCompanyDetail();

	void showHelp();

	void getBuildingByPos(int x, int y);

    void updateDisplay();

	void processOrders(const QString &order, BaseBuilding *);

    void changeType(BaseBuilding *, const QString &);

private:
    void updateCompanyInfo();

    void updateStatusBar(const QString &msg);

	// transforms double into QString
	static QString toString(double value);

	void setupBuildingInfoList();

	//inline void setupBuildingDetailDialog(BuildingDetailDialog *);

	inline void setupCompanyDetailDialog(CompanyDetailDialog *);

private:
    Company *playerCompany_;

	BuildingDetailDialog *buildingDetailDialog_;

	BuildingInfoList *buildingInfoList_;

	BuildingInfoWidget *buildingInfoWidget_;

	HelpDialog *helpDialog_;

	MainUI *mainUi_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
