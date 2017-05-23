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
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef WAREHOUSE_TABLE_WIDGET_H
#define WAREHOUSE_TABLE_WIDGET_H

#include <QTableWidget>

#include "Source/Objects/LandParcel.h"
#include "Source/Objects/Industry.h"
#include "Source/Objects/Goods.h"
#include "Source/Objects/Warehouse.h"

#include "TableWidgetPushButton.h"
#include "SelectTableWidget.h"

class WarehouseTableWidget : public QTableWidget {
    Q_OBJECT

public:
    WarehouseTableWidget(QWidget *parent = nullptr, Warehouse *warehouse = nullptr);

    void init();

    void setWarehouse(Warehouse *warehouse) { this->warehouse_ = warehouse; }

public slots:
    void goSelectIndustry();

    void getGoods(int index);

    void getDestAndSendPreroute(LandParcel *dest);

    void updateDisplay();

signals:
    void sendPreroute(const Goods &goods, Industry *dest);

private:
    Goods *goods_ = nullptr;

    Warehouse *warehouse_ = nullptr;

    SelectTableWidget *selectTableWidget_ = nullptr;
};

#endif // !WAREHOUSE_TABLE_WIDGET_H
