#ifndef UIMANAGER_H
#define UIMANAGER_H

class BankDialog;
class BuildingDetailDialog;
class CompanyDetailDialog;

class UIManager {
public:
	static UIManager &instance();

	BankDialog *bankDialog();

	BuildingDetailDialog *buildingDetailDialog();

	CompanyDetailDialog *companyDetailDialog();

private:
	UIManager();
	~UIManager();
	UIManager(const UIManager &) = delete;
	UIManager &operator=(const UIManager &) = delete;

	void init();

	BankDialog *bankDialog_;
	BuildingDetailDialog *buildingDetailDialog_;
	CompanyDetailDialog *companyDetailDialog_;
};

#endif // !UIMANAGER_H
