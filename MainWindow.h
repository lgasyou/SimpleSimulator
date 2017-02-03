#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class MyPushButton;
class BuildingBase;
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

    void showBuildingDetail(BuildingBase *building);
    void showCompanyDetail();
    void updateDisplay();

    void buy(BuildingBase *building);
    void sell(BuildingBase *building);
    void changeType(BuildingBase *, const QString &);
    void manage(BuildingBase *, const QString &);

private:
    void updateCompanyInfo();
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	static QString toString(double value);

    Company *company_;
    BankDialog *bankDialog_;
    BuildingDetailDialog *buildingDetailDialog_;
    BuildingInfoTableWidget *buildingInfoTableWidget_;
    CompanyDetailDialog *companyDetailDialog_;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
