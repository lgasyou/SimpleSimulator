#include "bankaccount.h"
#include "bank.h"

BankAccount::BankAccount() { }

BankAccount::~BankAccount() { }

void BankAccount::update() {
	deposit_ *= (1 + bank_->depositInterestRate());
	debt_	 *= (1 + bank_->loanInterestRate());
}
