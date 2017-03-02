#include "bank.h"

#include <QString>

Bank::Bank(const QString &name) :
	BaseFinance(name, "Bank")
{ }

Bank::~Bank() { }

void Bank::init() {
	depositInterestRate_ = 0.003;
	loanInterestRate_ = 0.008;
}

void Bank::closeAnAccount(Company *client) { }

void Bank::deposit(Company *client, double amount) { }

void Bank::loan(Company *client, double amount) { }

void Bank::openAnAccount(Company *client) { }

void Bank::repay(Company *client, double amount) { }

const BankClient &Bank::query(Company *client) {
	return findClient(client);
}

void Bank::withdraw(Company *client, double amount) { }

void Bank::update() { }

BankClient &Bank::findClient(Company *client) {
	for (BankClient &c : clientList_) {
		if (c.company() == client)
			return c;
	}

	static BankClient emptyClient;
	return emptyClient;
}
