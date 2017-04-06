#include "companymanager.h"
#include "company.h"

#include <algorithm>
#include <functional>

CompanyManager::CompanyManager() { }

CompanyManager::~CompanyManager() {
	delete playerCompany_;
}

CompanyManager &CompanyManager::instance() {
	static CompanyManager companyManager;
	return companyManager;
}

void CompanyManager::init() {
	playerCompany_ = new Company;
}

void CompanyManager::update() {
	playerCompany_->update();
	std::for_each(aiCompanyList_.begin(), aiCompanyList_.end(), [](Company *company) { company->update(); });
}
