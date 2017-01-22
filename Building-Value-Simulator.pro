#-------------------------------------------------
#
# Project created by QtCreator 2016-12-25T15:36:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Building-Value-Simulator
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    BaseBuilding.cpp \
    BuildingManager.cpp \
    Company.cpp \
    ValueGenerator.cpp \
    Residence.cpp \
    MyPushButton.cpp \
    GameTimer.cpp \
    BankDialog.cpp \
    BuildingDetailDialog.cpp \
    Factory.cpp \
    CompanyDetailDialog.cpp \
    FactoryCargo.cpp \
    FactoryCargoTableWidget.cpp \
    BuildingInfoTableWidget.cpp

HEADERS  += MainWindow.h \
    BaseBuilding.h \
    BuildingManager.h \
    Company.h \
    ValueGenerator.h \
    Residence.h \
    MyPushButton.h \
    GameTimer.h \
    BankDialog.h \
    Factory.h \
    CompanyDetailDialog.h \
    BuildingDetailDialog.h \
    FactoryCargo.h \
    FactoryCargoTableWidget.h \
    BuildingInfoTableWidget.h

FORMS    += MainWindow.ui \
    BankDialog.ui \
    BuildingDetailDialog.ui \
    CompanyDetailDialog.ui
