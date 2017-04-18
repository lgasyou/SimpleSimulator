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

#ifndef BANKDIALOG_H
#define BANKDIALOG_H

#include "QDialog"

class Company;

namespace Ui {
class BankDialog;
}

// Used in early version ONLY.
// @deprecated
class BankDialog : public QDialog {
    Q_OBJECT

public:
    explicit BankDialog(QWidget *parent = nullptr);

    ~BankDialog();

    void updateDisplay();

	// Displays according to whether the client has already lent money or not.
	void displayAccordingToClientStatus();

	void setClient(Company *client) { this->client_ = client; }

    static void setInterestRate(double interestRate) { interestRate_ = interestRate; }
    static double interestRate() { return interestRate_; }

private slots:
	// Sets datas with the input.
    void on_pushButton_Accept_clicked();

private:
	// transforms double into QString
	static QString toString(double value);

private:
    static double interestRate_;

    Company *client_;

    Ui::BankDialog *ui;
};

#endif // BANKDIALOG_H
