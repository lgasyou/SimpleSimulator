#ifndef BANKCLIENT_H
#define BANKCLIENT_H

class Company;

class BankClient {
public:
	BankClient();

	~BankClient();

	void update();

	void setDebt(double debt) { this->debt_ = debt; }
	double debt() const { return this->debt_; }

	void setDeposit(double deposit) { this->deposit_ = deposit; }
	double deposit() const { return this->deposit_; }

	void setCompany(Company *company) { this->company_ = company; }
	Company *company() const { return this->company_; }

private:
	double debt_;

	double deposit_;

	Company *company_;
};
#endif // !BANKCLIENT_H
