#include "companymanager.h"
#include "company.h"

#include <algorithm>
#include <functional>

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
	std::for_each(aiCompanyList_.begin(), aiCompanyList_.end(), std::mem_fun(&Company::update));
}
