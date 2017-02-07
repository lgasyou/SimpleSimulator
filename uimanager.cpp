#include "uimanager.h"

#include "bankdialog.h"
#include "buildingdetaildialog.h"
#include "companydetaildialog.h"

UIManager::UIManager() {
	init();
}

UIManager::~UIManager() {
	if (bankDialog_)
		delete bankDialog_;
	if (buildingDetailDialog_)
		delete buildingDetailDialog_;
	if (companyDetailDialog_)
		delete companyDetailDialog_;
}

void UIManager::init() {
	bankDialog_ = nullptr;
	buildingDetailDialog_ = nullptr;
	companyDetailDialog_ = nullptr;
}

UIManager &UIManager::instance() {
	static UIManager uiManager;
	return uiManager;
}

BankDialog *UIManager::bankDialog() {
	if (!bankDialog_)
		bankDialog_ = new BankDialog;
	return bankDialog_;
}

BuildingDetailDialog *UIManager::buildingDetailDialog() {
	if (!buildingDetailDialog_)
		buildingDetailDialog_ = new BuildingDetailDialog;
	return buildingDetailDialog_;
}

CompanyDetailDialog *UIManager::companyDetailDialog() {
	if (!companyDetailDialog_)
		companyDetailDialog_ = new CompanyDetailDialog;
	return companyDetailDialog_;
}
