#include "bank.h"
#include "company.h"

#include <QString>

Bank::Bank(const QString &name) :
	BaseFinance(name, "Bank")
{ }

Bank::~Bank() { }

void Bank::init() {
	depositInterestRate_ = 0.003;
	loanInterestRate_ = 0.008;
}

void Bank::closeAnAccount(Company *client) {
	const BankAccount &bankAccount = clientMap_[client];
	double finalCash = client->cash() + bankAccount.deposit() - bankAccount.debt();
	if (finalCash >= 0) {
		client->setCash(finalCash);
		clientMap_.erase(client);
	}
}

void Bank::deposit(Company *client, double amount) {
	BankAccount &bankAccount = clientMap_[client];
	double finalCash = client->cash() - amount;
	double finalDeposit = bankAccount.deposit() + amount;
	bankAccount.setDeposit(finalDeposit);
	client->setCash(finalCash);
}

void Bank::loan(Company *client, double amount) {
	BankAccount &bankAccount = clientMap_[client];
	double finalCash = client->cash() + amount;
	double finalDebt = bankAccount.debt() + amount;
	bankAccount.setDeposit(finalDebt);
	client->setCash(finalCash);
}

void Bank::openAnAccount(Company *client) {
	clientMap_[client].setBank(this);
}

void Bank::repay(Company *client, double amount) {
	BankAccount &bankAccount = clientMap_[client];
	double finalCash = client->cash() - amount;
	double finalDebt = bankAccount.debt() - amount;
	bankAccount.setDeposit(finalDebt);
	client->setCash(finalCash);
}

const BankAccount &Bank::query(Company *client) const {
	return clientMap_.find(client)->second;
}

void Bank::withdraw(Company *client, double amount) {
	BankAccount &bankAccount = clientMap_[client];
	double finalCash = client->cash() + amount;
	double finalDeposit = bankAccount.deposit() - amount;
	bankAccount.setDeposit(finalDeposit);
	client->setCash(finalCash);
}

void Bank::update() {
	for (auto &client : clientMap_) {
		client.second.update();
	}
}