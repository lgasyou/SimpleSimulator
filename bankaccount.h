#ifndef BANKCLIENT_H
#define BANKCLIENT_H

class Bank;
class Company;

class BankAccount {
public:
	BankAccount();

	~BankAccount();

	void update();

	void setDebt(double debt) { this->debt_ = debt; }
	double debt() const { return debt_; }

	void setDeposit(double deposit) { this->deposit_ = deposit; }
	double deposit() const { return deposit_; }

	void setBank(Bank *bank) { this->bank_ = bank; }

	void setCompany(Company *company) { this->company_ = company; }
	Company *company() const { return company_; }

private:
	double debt_ = 0.0;

	double deposit_ = 0.0;

	Bank *bank_ = nullptr;

	Company *company_ = nullptr;
};
#endif // !BANKCLIENT_H
