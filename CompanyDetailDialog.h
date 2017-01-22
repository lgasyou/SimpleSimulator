#ifndef COMPANYDETAILDIALOG_H
#define COMPANYDETAILDIALOG_H

#include <QDialog>

class Company;
namespace Ui {
class CompanyDetailDialog;
}

class CompanyDetailDialog : public QDialog {
    Q_OBJECT

public:
    explicit CompanyDetailDialog(QWidget *parent = 0);
    ~CompanyDetailDialog();

    inline void setCompany(Company *company) { this->company_ = company; }

public slots:
    void updateDisplay();

private:
	QString toString(double value);

    Company *company_;
    Ui::CompanyDetailDialog *ui;
};

#endif // COMPANYDETAILDIALOG_H
