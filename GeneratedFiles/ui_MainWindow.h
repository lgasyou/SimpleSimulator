/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *action_SaveAndExit;
    QAction *action_Load;
    QAction *actionExit_without_Save;
    QAction *action_New;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_OptionButtons;
    QPushButton *pushButton_Bank;
    QPushButton *pushButton_Company;
    QHBoxLayout *horizontalLayout_Labels;
    QLabel *label_CompanyName;
    QLabel *label_CompanyCash;
    QLabel *label_CompanyTotalValue;
    QLabel *label_Turns;
    QPushButton *pushButton_EndTurn;
    QVBoxLayout *BuildingInfoTableWidget;
    QMenuBar *menuBar;
    QMenu *menu_Files;
    QMenu *menu_Help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(665, 479);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QStringLiteral("action_Save"));
        action_SaveAndExit = new QAction(MainWindow);
        action_SaveAndExit->setObjectName(QStringLiteral("action_SaveAndExit"));
        action_Load = new QAction(MainWindow);
        action_Load->setObjectName(QStringLiteral("action_Load"));
        actionExit_without_Save = new QAction(MainWindow);
        actionExit_without_Save->setObjectName(QStringLiteral("actionExit_without_Save"));
        action_New = new QAction(MainWindow);
        action_New->setObjectName(QStringLiteral("action_New"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_OptionButtons = new QHBoxLayout();
        horizontalLayout_OptionButtons->setSpacing(6);
        horizontalLayout_OptionButtons->setObjectName(QStringLiteral("horizontalLayout_OptionButtons"));
        pushButton_Bank = new QPushButton(centralWidget);
        pushButton_Bank->setObjectName(QStringLiteral("pushButton_Bank"));

        horizontalLayout_OptionButtons->addWidget(pushButton_Bank);

        pushButton_Company = new QPushButton(centralWidget);
        pushButton_Company->setObjectName(QStringLiteral("pushButton_Company"));

        horizontalLayout_OptionButtons->addWidget(pushButton_Company);


        gridLayout->addLayout(horizontalLayout_OptionButtons, 2, 0, 1, 1);

        horizontalLayout_Labels = new QHBoxLayout();
        horizontalLayout_Labels->setSpacing(6);
        horizontalLayout_Labels->setObjectName(QStringLiteral("horizontalLayout_Labels"));
        label_CompanyName = new QLabel(centralWidget);
        label_CompanyName->setObjectName(QStringLiteral("label_CompanyName"));

        horizontalLayout_Labels->addWidget(label_CompanyName);

        label_CompanyCash = new QLabel(centralWidget);
        label_CompanyCash->setObjectName(QStringLiteral("label_CompanyCash"));

        horizontalLayout_Labels->addWidget(label_CompanyCash);

        label_CompanyTotalValue = new QLabel(centralWidget);
        label_CompanyTotalValue->setObjectName(QStringLiteral("label_CompanyTotalValue"));

        horizontalLayout_Labels->addWidget(label_CompanyTotalValue);

        label_Turns = new QLabel(centralWidget);
        label_Turns->setObjectName(QStringLiteral("label_Turns"));

        horizontalLayout_Labels->addWidget(label_Turns);


        gridLayout->addLayout(horizontalLayout_Labels, 0, 0, 1, 1);

        pushButton_EndTurn = new QPushButton(centralWidget);
        pushButton_EndTurn->setObjectName(QStringLiteral("pushButton_EndTurn"));

        gridLayout->addWidget(pushButton_EndTurn, 3, 0, 1, 1);

        BuildingInfoTableWidget = new QVBoxLayout();
        BuildingInfoTableWidget->setSpacing(6);
        BuildingInfoTableWidget->setObjectName(QStringLiteral("BuildingInfoTableWidget"));

        gridLayout->addLayout(BuildingInfoTableWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 665, 22));
        menu_Files = new QMenu(menuBar);
        menu_Files->setObjectName(QStringLiteral("menu_Files"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QStringLiteral("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_Files->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_Files->addAction(action_Save);
        menu_Files->addAction(action_Load);
        menu_Files->addAction(action_New);
        menu_Files->addAction(action_SaveAndExit);
        menu_Files->addAction(actionExit_without_Save);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", Q_NULLPTR));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", Q_NULLPTR));
        action_SaveAndExit->setText(QApplication::translate("MainWindow", "Save and &Exit", Q_NULLPTR));
        action_Load->setText(QApplication::translate("MainWindow", "&Load", Q_NULLPTR));
        actionExit_without_Save->setText(QApplication::translate("MainWindow", "Exit without Save", Q_NULLPTR));
        action_New->setText(QApplication::translate("MainWindow", "&New", Q_NULLPTR));
        pushButton_Bank->setText(QApplication::translate("MainWindow", "Bank", Q_NULLPTR));
        pushButton_Company->setText(QApplication::translate("MainWindow", "Company", Q_NULLPTR));
        label_CompanyName->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_CompanyCash->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_CompanyTotalValue->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_Turns->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        pushButton_EndTurn->setText(QApplication::translate("MainWindow", "End Turn", Q_NULLPTR));
        menu_Files->setTitle(QApplication::translate("MainWindow", "&Files", Q_NULLPTR));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
