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

void CompanyDetailDialog::updateDisplay() {
    if (this->isHidden())
        return;

    setWindowTitle(company_->name());
    ui->label_Name->setText(
                tr("Name:        ") + company_->name());
    ui->label_Cash->setText(
                tr("Cash:        $") + QString::number(company_->cash(), 10, 2));
    ui->label_TotalValue->setText(
                tr("Total Value: $") + QString::number(company_->totalValue(), 10, 2));
    ui->label_Liability->setText(company_->liability() > 0 ?
                tr("<code style=\"color:red\">Liability: $%1</code>").arg(QString::number(company_->liability(), 10, 2)) :
                tr("Liability:   $0"));
}
