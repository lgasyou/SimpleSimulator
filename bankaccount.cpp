#include "bankaccount.h"
#include "bank.h"

BankAccount::BankAccount() :
	deposit_(0.0),
	debt_(0.0),
	bank_(nullptr),
	company_(nullptr)
{ }

BankAccount::~BankAccount() { }

void BankAccount::update() {
	deposit_ *= (1 + bank_->depositInterestRate());
	debt_	 *= (1 + bank_->loanInterestRate());
}
