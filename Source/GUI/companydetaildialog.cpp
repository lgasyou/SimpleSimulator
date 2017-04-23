/*
 *  Copyright 2017 Li Zeqing
 *
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "companydetaildialog.h"

#include "ui_companydetaildialog.h"
#include "widgethelper.h"

CompanyDetailDialog::CompanyDetailDialog(QWidget *parent) :
    QDialog(parent),
    company_(nullptr),
    ui(new Ui::CompanyDetailDialog) {
    ui->setupUi(this);
}

CompanyDetailDialog::~CompanyDetailDialog() {
    delete ui;
}

void CompanyDetailDialog::updateDisplay() {
    // Return if this window isn't showing.
    if (this->isHidden())    return;

    const QString &name = company_->name();
    const QString &cash = WidgetHelper::toString(company_->cash());
    const QString &totalValue = WidgetHelper::toString(company_->totalValue());
    const QString &liability = WidgetHelper::toString(company_->liability());
    setWindowTitle(name);
    ui->label_Name->setText(tr("Name:        ") + name);
    ui->label_Cash->setText(tr("Cash:        $") + cash);
    ui->label_TotalValue->setText(tr("Total Value: $") + totalValue);
    ui->label_Liability->setText(tr("Liability:   $") + liability);
}