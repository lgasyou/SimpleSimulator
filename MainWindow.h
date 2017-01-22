#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class BuildingManager;
class Company;
class MyPushButton;
class BaseBuilding;
class BuildingDetailDialog;
class BuildingInfoTableWidget;
class CompanyDetailDialog;
class BankDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void dataChanged(bool);

private slots:
    void goBank();
    void endTurns();
    void showBuildingDetail(BaseBuilding *building);
    void showCompanyDetail();
    void updateDisplay();
    void buy(BaseBuilding *building);
    void sell(BaseBuilding *building);
    void changeType(BaseBuilding *, const QString &);
    void manage(BaseBuilding *, const QString &);

private:
    void updateCompanyInfo();
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	QString toString(double value);

    BuildingManager *buildingManager;
    Company *company;
    BankDialog *bankDialog;
    BuildingDetailDialog *buildingDetailDialog;
    BuildingInfoTableWidget *buildingInfoTableWidget;
    CompanyDetailDialog *companyDetailDialog;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
