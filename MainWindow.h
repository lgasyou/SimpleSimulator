#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void init();

signals:
    void dataChanged();

private slots:
    void goBank();
    void endTurns();

    void showBuildingDetail(BaseBuilding *building);
    void showCompanyDetail();
    void updateDisplay();

    void buy(BaseBuilding *building);
    void sell(BaseBuilding *building);
    void changeType(BaseBuilding *, const QString &);

private:
    void updateCompanyInfo();
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	static QString toString(double value);

	static void showDialog(QDialog *);

    Company *playerCompany_;
    BankDialog *bankDialog_;
    BuildingDetailDialog *buildingDetailDialog_;
    BuildingInfoTableWidget *buildingInfoTableWidget_;
    CompanyDetailDialog *companyDetailDialog_;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
