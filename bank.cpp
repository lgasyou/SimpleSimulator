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

const BankClient &Bank::query(Company *client) const {
	return clientList_.find(client)->second;
}

void Bank::withdraw(Company *client, double amount) { }

void Bank::update() { }