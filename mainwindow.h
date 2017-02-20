#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class BaseBuilding;

class MyPushButton;
class BuildingInfoTableWidget;
class BuildingInfoDialog;
class CompanyDetailDialog;

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
	// Opens bank dialog.
    void goBank();

	// Calls function update() of every variable objects.
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

	inline void setupBuildingInfoTableWidget();

	inline void setupBuildingInfoDialog(BuildingInfoDialog *);

	inline void setupCompanyDetailDialog(CompanyDetailDialog *);

private:
    Company *playerCompany_;

	BuildingInfoTableWidget *buildingInfoTableWidget_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
