#include "CompanyDetailDialog.h"
#include "Company.h"
#include "ui_CompanyDetailDialog.h"

CompanyDetailDialog::CompanyDetailDialog(QWidget *parent) :
    QDialog(parent),
    company_(nullptr),
    ui(new Ui::CompanyDetailDialog)
{
    ui->setupUi(this);

    connect(parent, SIGNAL(dataChanged(bool)),
            this, SLOT(updateDisplay()));
}

CompanyDetailDialog::~CompanyDetailDialog() {
    delete ui;
}

QString CompanyDetailDialog::toString(double value) {
	return QString::number(value, 10, 2);
}

void CompanyDetailDialog::updateDisplay() {
	// Return if this window isn't showing.
    if (this->isHidden())
        return;

    setWindowTitle(company_->name());
    ui->label_Name->setText(
                tr("Name:        ") + company_->name());
    ui->label_Cash->setText(
                tr("Cash:        $") + toString(company_->cash()));
    ui->label_TotalValue->setText(
                tr("Total Value: $") + toString(company_->totalValue()));
    ui->label_Liability->setText(company_->liability() > 0 ?
                tr("<code style=\"color:red\">Liability: $%1</code>").arg(toString(company_->liability())) :
                tr("Liability:   $0"));
}
