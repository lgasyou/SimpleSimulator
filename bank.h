#ifndef BANK_H
#define BANK_H

#include "basefinance.h"
#include "bankclient.h"
#include <list>

class Company;

class QString;

class Bank : public BaseFinance {
public:
	Bank(const QString &name = "Bank");

	~Bank();

	void init();

	void closeAnAccount(Company *client);

	void deposit(Company *client, double amount);

	void loan(Company *client, double amount);

	void openAnAccount(Company *client);

	void repay(Company *client, double amount);

	const BankClient &query(Company *client);

	void withdraw(Company *client, double amount);

	void update();

	void setDepositInterestRate(double depositInterestRate) { this->depositInterestRate_ = depositInterestRate; }
	double depositInterestRate() const { return this->depositInterestRate_; }

	void setLoanInterestRate(double loanInterestRate) { this->loanInterestRate_ = loanInterestRate; }
	double loanInterestRate() const { return this->loanInterestRate_; }

private:
	BankClient &findClient(Company *client);

private:
	std::list<BankClient> clientList_;

	double depositInterestRate_;

	double loanInterestRate_;
};

#endif // !BANK_H
