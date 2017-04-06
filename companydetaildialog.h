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
    explicit CompanyDetailDialog(QWidget *parent = nullptr);

    ~CompanyDetailDialog();

	void showUp();

    void setCompany(Company *company) { this->company_ = company; }

public slots:
    void updateDisplay();

private:
    Company *company_;

    Ui::CompanyDetailDialog *ui;
};

inline void CompanyDetailDialog::showUp() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // COMPANYDETAILDIALOG_H
