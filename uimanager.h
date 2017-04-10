#ifndef UIMANAGER_H
#define UIMANAGER_H

class BankDialog;
class BuildingDetailDialog;
class CompanyDetailDialog;
class SetRouteDialog;

// For now this class is only the prototype of UIManager.
// It returns the UI components by its methods.
// But in fact, I don't understand what should it be used for.
// deprecated.
class UIManager {
public:
	// Use singleton pattern.
	static UIManager &instance();

	BankDialog *bankDialog();

	BuildingDetailDialog *buildingDetailDialog();

	CompanyDetailDialog *companyDetailDialog();

	SetRouteDialog *setRouteDialog();

private:
	// Hide constructor and destructor.
	UIManager();

	~UIManager();

private:
	BankDialog *bankDialog_ = nullptr;

	BuildingDetailDialog *buildingDetailDialog_ = nullptr;

	CompanyDetailDialog *companyDetailDialog_ = nullptr;

	SetRouteDialog *setRouteDialog_ = nullptr;
};

#endif // !UIMANAGER_H
