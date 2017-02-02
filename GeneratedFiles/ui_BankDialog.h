/********************************************************************************
** Form generated from reading UI file 'BankDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BANKDIALOG_H
#define UI_BANKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_BankDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_Repay;
    QLabel *label_Repay;
    QSpinBox *spinBox_Repay;
    QSlider *horizontalSlider_Repay;
    QHBoxLayout *horizontalLayout_Borrow;
    QLabel *label_Borrow;
    QSpinBox *spinBox_Borrow;
    QSlider *horizontalSlider_Borrow;
    QHBoxLayout *horizontalLayout;
    QLabel *label_InterestRate;
    QLabel *label_Liability;
    QPushButton *pushButton_Accept;

    void setupUi(QDialog *BankDialog)
    {
        if (BankDialog->objectName().isEmpty())
            BankDialog->setObjectName(QStringLiteral("BankDialog"));
        BankDialog->resize(357, 129);
        gridLayout = new QGridLayout(BankDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_Repay = new QHBoxLayout();
        horizontalLayout_Repay->setObjectName(QStringLiteral("horizontalLayout_Repay"));
        label_Repay = new QLabel(BankDialog);
        label_Repay->setObjectName(QStringLiteral("label_Repay"));

        horizontalLayout_Repay->addWidget(label_Repay);

        spinBox_Repay = new QSpinBox(BankDialog);
        spinBox_Repay->setObjectName(QStringLiteral("spinBox_Repay"));

        horizontalLayout_Repay->addWidget(spinBox_Repay);

        horizontalSlider_Repay = new QSlider(BankDialog);
        horizontalSlider_Repay->setObjectName(QStringLiteral("horizontalSlider_Repay"));
        horizontalSlider_Repay->setOrientation(Qt::Horizontal);

        horizontalLayout_Repay->addWidget(horizontalSlider_Repay);


        gridLayout->addLayout(horizontalLayout_Repay, 2, 0, 1, 1);

        horizontalLayout_Borrow = new QHBoxLayout();
        horizontalLayout_Borrow->setObjectName(QStringLiteral("horizontalLayout_Borrow"));
        label_Borrow = new QLabel(BankDialog);
        label_Borrow->setObjectName(QStringLiteral("label_Borrow"));

        horizontalLayout_Borrow->addWidget(label_Borrow);

        spinBox_Borrow = new QSpinBox(BankDialog);
        spinBox_Borrow->setObjectName(QStringLiteral("spinBox_Borrow"));

        horizontalLayout_Borrow->addWidget(spinBox_Borrow);

        horizontalSlider_Borrow = new QSlider(BankDialog);
        horizontalSlider_Borrow->setObjectName(QStringLiteral("horizontalSlider_Borrow"));
        horizontalSlider_Borrow->setOrientation(Qt::Horizontal);

        horizontalLayout_Borrow->addWidget(horizontalSlider_Borrow);


        gridLayout->addLayout(horizontalLayout_Borrow, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_InterestRate = new QLabel(BankDialog);
        label_InterestRate->setObjectName(QStringLiteral("label_InterestRate"));

        horizontalLayout->addWidget(label_InterestRate);

        label_Liability = new QLabel(BankDialog);
        label_Liability->setObjectName(QStringLiteral("label_Liability"));

        horizontalLayout->addWidget(label_Liability);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        pushButton_Accept = new QPushButton(BankDialog);
        pushButton_Accept->setObjectName(QStringLiteral("pushButton_Accept"));

        gridLayout->addWidget(pushButton_Accept, 3, 0, 1, 1);


        retranslateUi(BankDialog);

        QMetaObject::connectSlotsByName(BankDialog);
    } // setupUi

    void retranslateUi(QDialog *BankDialog)
    {
        BankDialog->setWindowTitle(QApplication::translate("BankDialog", "Dialog", Q_NULLPTR));
        label_Repay->setText(QApplication::translate("BankDialog", "TextLabel", Q_NULLPTR));
        label_Borrow->setText(QApplication::translate("BankDialog", "TextLabel", Q_NULLPTR));
        label_InterestRate->setText(QApplication::translate("BankDialog", "TextLabel", Q_NULLPTR));
        label_Liability->setText(QApplication::translate("BankDialog", "TextLabel", Q_NULLPTR));
        pushButton_Accept->setText(QApplication::translate("BankDialog", "Accept", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BankDialog: public Ui_BankDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BANKDIALOG_H
