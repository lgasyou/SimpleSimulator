#include "companymanager.h"
#include "company.h"

CompanyManager::CompanyManager() {
	playerCompany_ = new Company;
}

CompanyManager::~CompanyManager() {
	delete playerCompany_;
}

CompanyManager &CompanyManager::instance() {
	static CompanyManager companyManager;
	return companyManager;
}

void CompanyManager::update() {
	playerCompany_->update();
	for (auto &aiCompany : aiCompanyList_)
		aiCompany->update();
}
