#ifndef COMPANYMANAGER_H
#define COMPANYMANAGER_H

#include <list>

class Company;

class CompanyManager {
public:
	// Use singleton pattern.
	static CompanyManager &instance();

	void init();

	void update();

	Company *playerCompany() { return playerCompany_; }

	std::list<Company *> &AICompanyList() { return AICompanyList_; }

private:
	// Hide constructor and destructor.
	CompanyManager();

	~CompanyManager();

private:
	Company *playerCompany_;

	std::list<Company *> AICompanyList_;
};


#endif // !COMPANYMANAGER_H