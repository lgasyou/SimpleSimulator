/********************************************************************************
** Form generated from reading UI file 'BuildingDetailDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDINGDETAILDIALOG_H
#define UI_BUILDINGDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BuildingDetailDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_Cargo;
    QLabel *label_CargoSum;
    QVBoxLayout *verticalLayout_Build;
    QPushButton *pushButton_Build_Factory;
    QPushButton *pushButton_Build_residence;
    QVBoxLayout *verticalLayout_Main;
    QPushButton *pushButton_Buy;
    QPushButton *pushButton_Sell;
    QPushButton *pushButton_Build;
    QPushButton *pushButton_Manage;
    QPushButton *pushButton_Dismantle;
    QVBoxLayout *verticalLayout_Info;
    QLabel *label_Name;
    QSpacerItem *verticalSpacer;
    QLabel *label_Value;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_Type;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_Owner;

    void setupUi(QDialog *BuildingDetailDialog)
    {
        if (BuildingDetailDialog->objectName().isEmpty())
            BuildingDetailDialog->setObjectName(QStringLiteral("BuildingDetailDialog"));
        BuildingDetailDialog->resize(594, 159);
        gridLayout = new QGridLayout(BuildingDetailDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_Cargo = new QVBoxLayout();
        verticalLayout_Cargo->setObjectName(QStringLiteral("verticalLayout_Cargo"));
        label_CargoSum = new QLabel(BuildingDetailDialog);
        label_CargoSum->setObjectName(QStringLiteral("label_CargoSum"));

        verticalLayout_Cargo->addWidget(label_CargoSum);


        gridLayout->addLayout(verticalLayout_Cargo, 1, 3, 1, 1);

        verticalLayout_Build = new QVBoxLayout();
        verticalLayout_Build->setObjectName(QStringLiteral("verticalLayout_Build"));
        pushButton_Build_Factory = new QPushButton(BuildingDetailDialog);
        pushButton_Build_Factory->setObjectName(QStringLiteral("pushButton_Build_Factory"));

        verticalLayout_Build->addWidget(pushButton_Build_Factory);

        pushButton_Build_residence = new QPushButton(BuildingDetailDialog);
        pushButton_Build_residence->setObjectName(QStringLiteral("pushButton_Build_residence"));

        verticalLayout_Build->addWidget(pushButton_Build_residence);


        gridLayout->addLayout(verticalLayout_Build, 1, 2, 1, 1);

        verticalLayout_Main = new QVBoxLayout();
        verticalLayout_Main->setObjectName(QStringLiteral("verticalLayout_Main"));
        pushButton_Buy = new QPushButton(BuildingDetailDialog);
        pushButton_Buy->setObjectName(QStringLiteral("pushButton_Buy"));

        verticalLayout_Main->addWidget(pushButton_Buy);

        pushButton_Sell = new QPushButton(BuildingDetailDialog);
        pushButton_Sell->setObjectName(QStringLiteral("pushButton_Sell"));

        verticalLayout_Main->addWidget(pushButton_Sell);

        pushButton_Build = new QPushButton(BuildingDetailDialog);
        pushButton_Build->setObjectName(QStringLiteral("pushButton_Build"));

        verticalLayout_Main->addWidget(pushButton_Build);

        pushButton_Manage = new QPushButton(BuildingDetailDialog);
        pushButton_Manage->setObjectName(QStringLiteral("pushButton_Manage"));

        verticalLayout_Main->addWidget(pushButton_Manage);

        pushButton_Dismantle = new QPushButton(BuildingDetailDialog);
        pushButton_Dismantle->setObjectName(QStringLiteral("pushButton_Dismantle"));

        verticalLayout_Main->addWidget(pushButton_Dismantle);


        gridLayout->addLayout(verticalLayout_Main, 1, 1, 1, 1);

        verticalLayout_Info = new QVBoxLayout();
        verticalLayout_Info->setObjectName(QStringLiteral("verticalLayout_Info"));
        label_Name = new QLabel(BuildingDetailDialog);
        label_Name->setObjectName(QStringLiteral("label_Name"));

        verticalLayout_Info->addWidget(label_Name);

        verticalSpacer = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_Info->addItem(verticalSpacer);

        label_Value = new QLabel(BuildingDetailDialog);
        label_Value->setObjectName(QStringLiteral("label_Value"));

        verticalLayout_Info->addWidget(label_Value);

        verticalSpacer_2 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_Info->addItem(verticalSpacer_2);

        label_Type = new QLabel(BuildingDetailDialog);
        label_Type->setObjectName(QStringLiteral("label_Type"));

        verticalLayout_Info->addWidget(label_Type);

        verticalSpacer_3 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_Info->addItem(verticalSpacer_3);

        label_Owner = new QLabel(BuildingDetailDialog);
        label_Owner->setObjectName(QStringLiteral("label_Owner"));

        verticalLayout_Info->addWidget(label_Owner);


        gridLayout->addLayout(verticalLayout_Info, 1, 0, 1, 1);


        retranslateUi(BuildingDetailDialog);

        QMetaObject::connectSlotsByName(BuildingDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *BuildingDetailDialog)
    {
        BuildingDetailDialog->setWindowTitle(QApplication::translate("BuildingDetailDialog", "Dialog", Q_NULLPTR));
        label_CargoSum->setText(QApplication::translate("BuildingDetailDialog", "TextLabel", Q_NULLPTR));
        pushButton_Build_Factory->setText(QApplication::translate("BuildingDetailDialog", "Factory", Q_NULLPTR));
        pushButton_Build_residence->setText(QApplication::translate("BuildingDetailDialog", "Residence", Q_NULLPTR));
        pushButton_Buy->setText(QApplication::translate("BuildingDetailDialog", "Buy", Q_NULLPTR));
        pushButton_Sell->setText(QApplication::translate("BuildingDetailDialog", "Sell", Q_NULLPTR));
        pushButton_Build->setText(QApplication::translate("BuildingDetailDialog", "Build", Q_NULLPTR));
        pushButton_Manage->setText(QApplication::translate("BuildingDetailDialog", "Manage", Q_NULLPTR));
        pushButton_Dismantle->setText(QApplication::translate("BuildingDetailDialog", "Dismantle", Q_NULLPTR));
        label_Name->setText(QApplication::translate("BuildingDetailDialog", "TextLabel", Q_NULLPTR));
        label_Value->setText(QApplication::translate("BuildingDetailDialog", "TextLabel", Q_NULLPTR));
        label_Type->setText(QApplication::translate("BuildingDetailDialog", "TextLabel", Q_NULLPTR));
        label_Owner->setText(QApplication::translate("BuildingDetailDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BuildingDetailDialog: public Ui_BuildingDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDINGDETAILDIALOG_H
