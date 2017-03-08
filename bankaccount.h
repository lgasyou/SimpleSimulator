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
	double debt() const { return this->debt_; }

	void setDeposit(double deposit) { this->deposit_ = deposit; }
	double deposit() const { return this->deposit_; }

	void setBank(Bank *bank) { this->bank_ = bank; }

	void setCompany(Company *company) { this->company_ = company; }
	Company *company() const { return this->company_; }

private:
	double debt_;

	double deposit_;

	Bank *bank_;

	Company *company_;
};
#endif // !BANKCLIENT_H