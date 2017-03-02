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

	inline Company *playerCompany() { return this->playerCompany_; }

	inline std::list<Company *> &aiCompanyList() { return aiCompanyList_; }

private:
	// Hide constructor and destructor.
	CompanyManager();

	~CompanyManager();

	CompanyManager(const CompanyManager &) = delete;

	CompanyManager &operator=(const CompanyManager &) = delete;

private:
	Company *playerCompany_;

	std::list<Company *> aiCompanyList_;
};


#endif // !COMPANYMANAGER_H