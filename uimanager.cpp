#include "uimanager.h"

#include "bankdialog.h"
#include "buildinginfodialog.h"
#include "companydetaildialog.h"
#include "setroutedialog.h"

UIManager::UIManager() { }

UIManager::~UIManager() { }

void UIManager::init() {
	bankDialog_ = nullptr;
	buildingDetailDialog_ = nullptr;
	companyDetailDialog_ = nullptr;
	setRouteDialog_ = nullptr;
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

BuildingInfoDialog *UIManager::buildingDetailDialog() {
	if (!buildingDetailDialog_)
		buildingDetailDialog_ = new BuildingInfoDialog;
	return buildingDetailDialog_;
}

CompanyDetailDialog *UIManager::companyDetailDialog() {
	if (!companyDetailDialog_)
		companyDetailDialog_ = new CompanyDetailDialog;
	return companyDetailDialog_;
}

SetRouteDialog *UIManager::setRouteDialog() {
	if (!setRouteDialog_)
		setRouteDialog_ = new SetRouteDialog;
	return setRouteDialog_;
}
