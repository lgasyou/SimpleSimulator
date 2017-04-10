#ifndef BANKDIALOG_H
#define BANKDIALOG_H

#include <QDialog>

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
