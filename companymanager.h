#ifndef COMPANYMANAGER_H
#define COMPANYMANAGER_H

#include <QList>

class Company;

class CompanyManager {
public:
	// Use singleton pattern.
	static CompanyManager &instance();

	void update();

	inline Company *playerCompany() { return this->playerCompany_; }

	inline QList<Company *> &aiCompanyList() { return aiCompanyList_; }

private:
	// Hide constructor and destructor.
	CompanyManager();

	~CompanyManager();

	CompanyManager(const CompanyManager &) = delete;

	CompanyManager &operator=(const CompanyManager &) = delete;

private:
	Company *playerCompany_;

	QList<Company *> aiCompanyList_;
};


#endif // !COMPANYMANAGER_H