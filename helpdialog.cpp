#include "helpdialog.h"
#include "ui_helpdialog.h"
#include "industrychainmanager.h"

#include <QStringList>

HelpDialog::HelpDialog(QDialog *parent) : QDialog(parent) {
	ui = new Ui::HelpDialog;
	ui->setupUi(this); 
	setWindowTitle(tr("Help"));

	init();
}

HelpDialog::~HelpDialog() {
	delete ui;
}

void HelpDialog::init() {
	connect(ui->itemListWidget, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)),
		this, SLOT(showIndustryChain(QListWidgetItem *)));

	QStringList items{ "Coal", "Iron", "Log", "Plank", "Steel"  };
	ui->itemListWidget->addItems(items);

	QStringList header{ "Item", "Weight" };

	ui->sourceTableWidget->setColumnCount(2);
	ui->sourceTableWidget->setHorizontalHeaderLabels(header);
	ui->productTableWidget->setColumnCount(2);
	ui->productTableWidget->setHorizontalHeaderLabels(header);
}

void HelpDialog::showIndustryChain(QListWidgetItem *item) {
	auto &precursors = IndustryChainManager::instance().precursors(item->text());
	int size = (int)precursors.size();
	ui->sourceTableWidget->setRowCount(size);
	for (int i = 0; i != size; ++i) {
		const QString &itemName = precursors[i].name;
		ui->sourceTableWidget->setItem(i, 0, new QTableWidgetItem(itemName));
		const QString &itemWeight = QString::number(precursors[i].volume, 10, 2);
		ui->sourceTableWidget->setItem(i, 1, new QTableWidgetItem(itemWeight));
	}

	ui->productTableWidget->setRowCount(1);
	const QString &itemName = item->text();
	ui->productTableWidget->setItem(0, 0, new QTableWidgetItem(itemName));
	const QString &itemWeight = QString::number(1);
	ui->productTableWidget->setItem(0, 1, new QTableWidgetItem(itemWeight));
}
