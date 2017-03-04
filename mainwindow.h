#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class BaseBuilding;

class MyPushButton;
class BuildingDetailDialog;
class BuildingInfoList;
class CompanyDetailDialog;
class HelpDialog;
class QString;

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
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	static QString toString(double value);

	void signalSlotConfig();

private:
    Company *playerCompany_;

	BuildingDetailDialog *buildingDetailDialog_;

	BuildingInfoList *buildingInfoList_;

	CompanyDetailDialog *companyDetailDialog_;

	HelpDialog *helpDialog_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
