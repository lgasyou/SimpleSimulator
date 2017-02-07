#include "bankdialog.h"
#include "company.h"
#include "ui_bankdialog.h"
#include <QString>

BankDialog::BankDialog(QWidget *parent) :
    QDialog(parent),
    client_(nullptr),
    ui(new Ui::BankDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("Welcome to the Bank!"));
    connect(ui->horizontalSlider_Borrow, SIGNAL(valueChanged(int)),
            ui->spinBox_Borrow, SLOT(setValue(int)));
    connect(ui->spinBox_Borrow, SIGNAL(valueChanged(int)),
            ui->horizontalSlider_Borrow, SLOT(setValue(int)));

    connect(ui->horizontalSlider_Repay, SIGNAL(valueChanged(int)),
            ui->spinBox_Repay, SLOT(setValue(int)));
    connect(ui->spinBox_Repay, SIGNAL(valueChanged(int)),
            ui->horizontalSlider_Repay, SLOT(setValue(int)));
}

BankDialog::~BankDialog() {
    delete ui;
}

void BankDialog::updateDisplay() {
    const QString &liability = tr("Liability: $") + toString(client_->liability());
	const QString &interestRate = tr("Interest Rate: ") + toString(interestRate_ * 100) + "%";
	ui->label_InterestRate->setText(interestRate);
    ui->label_Liability->setText(liability);

    ui->horizontalSlider_Borrow->setValue(0);
    ui->horizontalSlider_Repay->setValue(0);

	displayAccordingToClientStatus();
}

void BankDialog::displayAccordingToClientStatus() {
	if (client_->liability() == 0) {
		ui->label_Borrow->show();
		ui->horizontalSlider_Borrow->show();
		ui->spinBox_Borrow->show();
		ui->label_Repay->hide();
		ui->horizontalSlider_Repay->hide();
		ui->spinBox_Repay->hide();

		ui->horizontalSlider_Borrow->setRange(0, 500);
		ui->spinBox_Borrow->setRange(0, 500);
		ui->label_Borrow->setText(tr("Borrow:"));
	} else {
		ui->label_Repay->show();
		ui->horizontalSlider_Repay->show();
		ui->spinBox_Repay->show();
		ui->label_Borrow->hide();
		ui->horizontalSlider_Borrow->hide();
		ui->spinBox_Borrow->hide();

		ui->horizontalSlider_Repay->setRange(0, client_->liability());
		ui->spinBox_Repay->setRange(0, client_->liability());
		ui->spinBox_Repay->setMinimumSize(ui->spinBox_Borrow->sizeHint());
		ui->horizontalSlider_Repay->setValue(0);
		ui->label_Repay->setText(tr("Repay: "));
	}
}

void BankDialog::on_pushButton_Accept_clicked() {
    double brought = ui->horizontalSlider_Borrow->value(),
            repay  = ui->horizontalSlider_Repay->value();
    double needRepay = brought * (1 + interestRate_);
    client_->setCash(client_->cash() + brought - repay);
    client_->setTotalValue(client_->totalValue() + brought - repay);
    client_->setLiability(client_->liability() + needRepay - repay);
    accept();
}

QString BankDialog::toString(double value) {
	return QString::number(value, 10, 2);
}

double BankDialog::interestRate_ = 0.1;
