#ifndef BANKDIALOG_H
#define BANKDIALOG_H

class BankClient;
class Company;
#include <QMap>
#include <QDialog>

namespace Ui {
class BankDialog;
}

class BankDialog : public QDialog {
    Q_OBJECT

public:
    explicit BankDialog(Company *client, QWidget *parent = 0);
    ~BankDialog();

    void updateDisplay();

    static void setInterestRate(double interestRate) { interestRate_ = interestRate; }
    static const double interestRate() { return interestRate_; }

private slots:
    void on_pushButton_Accept_clicked();

private:
    static double interestRate_;
    Company *client_;
    Ui::BankDialog *ui;
};

#endif // BANKDIALOG_H
