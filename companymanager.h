#ifndef COMPANYMANAGER_H
#define COMPANYMANAGER_H

#include <QList>

class Company;

class CompanyManager {
public:
	static CompanyManager &instance();

	Company *playerCompany() { return this->playerCompany_; }

private:
	CompanyManager();
	~CompanyManager();
	CompanyManager(const CompanyManager &) = delete;
	CompanyManager &operator=(const CompanyManager &) = delete;

	Company *playerCompany_;

	QList<Company *> aiCompany_;
};


#endif // !COMPANYMANAGER_H