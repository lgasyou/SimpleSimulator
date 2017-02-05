#include "companymanager.h"
#include "company.h"

CompanyManager::CompanyManager() {
	playerCompany_ = new Company;
}

CompanyManager::~CompanyManager() { }

CompanyManager &CompanyManager::instance() {
	static CompanyManager companyManager;
	return companyManager;
}
