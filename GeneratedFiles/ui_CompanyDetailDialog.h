/********************************************************************************
** Form generated from reading UI file 'CompanyDetailDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMPANYDETAILDIALOG_H
#define UI_COMPANYDETAILDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_CompanyDetailDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label_Name;
    QLabel *label_Cash;
    QLabel *label_TotalValue;
    QLabel *label_Liability;

    void setupUi(QDialog *CompanyDetailDialog)
    {
        if (CompanyDetailDialog->objectName().isEmpty())
            CompanyDetailDialog->setObjectName(QStringLiteral("CompanyDetailDialog"));
        CompanyDetailDialog->resize(400, 300);
        gridLayout = new QGridLayout(CompanyDetailDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_Name = new QLabel(CompanyDetailDialog);
        label_Name->setObjectName(QStringLiteral("label_Name"));

        gridLayout->addWidget(label_Name, 0, 0, 1, 1);

        label_Cash = new QLabel(CompanyDetailDialog);
        label_Cash->setObjectName(QStringLiteral("label_Cash"));

        gridLayout->addWidget(label_Cash, 1, 0, 1, 1);

        label_TotalValue = new QLabel(CompanyDetailDialog);
        label_TotalValue->setObjectName(QStringLiteral("label_TotalValue"));

        gridLayout->addWidget(label_TotalValue, 2, 0, 1, 1);

        label_Liability = new QLabel(CompanyDetailDialog);
        label_Liability->setObjectName(QStringLiteral("label_Liability"));

        gridLayout->addWidget(label_Liability, 3, 0, 1, 1);


        retranslateUi(CompanyDetailDialog);

        QMetaObject::connectSlotsByName(CompanyDetailDialog);
    } // setupUi

    void retranslateUi(QDialog *CompanyDetailDialog)
    {
        CompanyDetailDialog->setWindowTitle(QApplication::translate("CompanyDetailDialog", "Dialog", Q_NULLPTR));
        label_Name->setText(QApplication::translate("CompanyDetailDialog", "TextLabel", Q_NULLPTR));
        label_Cash->setText(QApplication::translate("CompanyDetailDialog", "TextLabel", Q_NULLPTR));
        label_TotalValue->setText(QApplication::translate("CompanyDetailDialog", "TextLabel", Q_NULLPTR));
        label_Liability->setText(QApplication::translate("CompanyDetailDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CompanyDetailDialog: public Ui_CompanyDetailDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMPANYDETAILDIALOG_H
