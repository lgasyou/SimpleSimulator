#ifndef BANKCLIENT_H
#define BANKCLIENT_H

class Company;

class BankClient {
public:
	BankClient();

	~BankClient();

	void setCompany(Company *company) { this->company_ = company; }
	Company *company() const { return this->company_; }

private:
	Company *company_;
};
#endif // !BANKCLIENT_H
