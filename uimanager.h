#ifndef UIMANAGER_H
#define UIMANAGER_H

class BankDialog;
class BuildingDetailDialog;
class CompanyDetailDialog;
class SetRouteDialog;

// For now this class is only the prototype of UIManager.
// It returns the UI componments by its methods.
// But in fact, I don't understand what should it be used for.
class UIManager {
public:
	static UIManager &instance();

	BankDialog *bankDialog();

	BuildingDetailDialog *buildingDetailDialog();

	CompanyDetailDialog *companyDetailDialog();

	SetRouteDialog *setRouteDialog();

private:
	UIManager();
	~UIManager();
	UIManager(const UIManager &) = delete;
	UIManager &operator=(const UIManager &) = delete;

	void init();

	BankDialog *bankDialog_;
	BuildingDetailDialog *buildingDetailDialog_;
	CompanyDetailDialog *companyDetailDialog_;
	SetRouteDialog *setRouteDialog_;
};

#endif // !UIMANAGER_H
