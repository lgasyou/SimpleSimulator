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

	inline void showAndRaise();

    inline void setCompany(Company *company) { this->company_ = company; }

public slots:
    void updateDisplay();

private:
	// transforms double into QString
	static QString toString(double value);

    Company *company_;
    Ui::CompanyDetailDialog *ui;
};

inline void CompanyDetailDialog::showAndRaise() {
	this->show();
	this->raise();
	this->activateWindow();
}

#endif // COMPANYDETAILDIALOG_H
