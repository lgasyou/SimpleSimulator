/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Company;
class BaseBuilding;

class TableWidgetPushButton;
class BuildingDetailDialog;
class BuildingTableWidget;
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

	void showBuildingTableWidget();

    void showCompanyDetail();

	void showHelp();

	void getBuildingByPos(int x, int y);

    void updateDisplay();

	void processCommand(int command, BaseBuilding *);

private:
    void updateStatusBar(const QString &msg);

	// transforms double into QString
	// Retains two decimals.
	static QString toString(double value);

	void signalSlotConfig();

private:
    Company *playerCompany_;

	BuildingDetailDialog *buildingDetailDialog_;

	BuildingTableWidget *buildingInfoList_;

	CompanyDetailDialog *companyDetailDialog_;

	HelpDialog *helpDialog_;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
