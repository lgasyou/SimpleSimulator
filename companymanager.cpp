#include "companymanager.h"
#include "company.h"

#include <algorithm>
#include <functional>

CompanyManager::CompanyManager() { }

CompanyManager::~CompanyManager() {
	delete playerCompany_;
	for (Company *AICompany : AICompanyList_) {
		delete AICompany;
	}
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
	std::for_each(AICompanyList_.begin(), AICompanyList_.end(), [](Company *company) { company->update(); });
}
