#include "BuildingInfoTableWidget.h"
#include "BuildingManager.h"
#include "Company.h"
#include "MyPushButton.h"
#include <QFile>
#include <QApplication>

BuildingInfoTableWidget::BuildingInfoTableWidget(QWidget *parent) :
    QTableWidget(parent),
    buildingManager_(nullptr),
    company_(nullptr)
{
	this->setColumnCount(BuildingBase::numberOfProperties + 2);
	QStringList header{ tr("Name"),tr("Value"),tr("Type"), tr("Ownership"),tr("Option"), tr("Option") };
	this->setHorizontalHeaderLabels(header);
}

bool BuildingInfoTableWidget::writeFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    QApplication::setOverrideCursor(Qt::WaitCursor);
//    for (int row = 0; row != buildingManager_->buildingNumber(); ++row) {
//        for (int col = 0; col != BaseBuilding::numberOfProperties; ++ col) {
//            QString str;

//        }
//    }
    QApplication::restoreOverrideCursor();
    return true;
}

bool BuildingInfoTableWidget::readFile(const QString &fileName) {
    QFile file(fileName);
    return true;
}

void BuildingInfoTableWidget::updateDisplay() {
    int buildingNumber = buildingManager_->buildingNumber();
    this->setRowCount(buildingNumber);

    for (int i = 0; i != buildingNumber; ++i) {
        auto building = buildingManager_->getBuildingById(i);

        this->setItem(i, 0, new QTableWidgetItem(building->name()));
        QString deltaValue = " " + toString(building->deltaValue());
        QString value = "$" + toString(building->value()) + deltaValue;
        this->setItem(i, 1, new QTableWidgetItem(value));
        this->setItem(i, 2, new QTableWidgetItem(building->type()));
        QString owner = building->owner() ? building->owner()->name() : tr("Government");
        this->setItem(i, 3, new QTableWidgetItem(owner));

        QString btnText = (building->owner() != company_) ? tr("Buy") : tr("Sell");
        MyPushButton *optionBtn = new MyPushButton(btnText);
        connect(optionBtn, SIGNAL(sendPointer(MyPushButton*)),
                this, SLOT(getBuildingAndSendSignal(MyPushButton*)));
        this->setCellWidget(i, 4, optionBtn);

        MyPushButton *detailBtn = new MyPushButton(tr("Details"));
        connect(detailBtn, SIGNAL(sendPointer(MyPushButton*)),
                this, SLOT(getBuildingAndSendSignal(MyPushButton*)));
        this->setCellWidget(i, 5, detailBtn);
    }
}

QString BuildingInfoTableWidget::toString(double value) {
	return QString::number(value, 10, 2);
}

void BuildingInfoTableWidget::getBuildingAndSendSignal(MyPushButton *button) {
    int x = button->frameGeometry().x(),
        y = button->frameGeometry().y();
    QModelIndex index = this->indexAt(QPoint(x, y));
    int id = index.row();
    BuildingBase *building = buildingManager_->getBuildingById(id);

    if (button->text() == "Buy") {
        emit buySignal(building);
    } else if (button->text() == "Sell") {
        emit sellSignal(building);
    } else {
        emit showDetailSignal(building);
    }
}
