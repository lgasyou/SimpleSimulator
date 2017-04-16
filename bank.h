/*
 *	Copyright 2017 Li Zeqing
 *
 *	This file is part of World Simulator.
 *	
 *	World Simulator is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU Lesser General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *	
 *	World Simulator is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *	
 *	You should have received a copy of the GNU Lesser General Public License
 *	along with World Simulator.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BANK_H
#define BANK_H

#include "basefinance.h"
#include "bankaccount.h"
#include <map>

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

	const BankAccount &query(Company *client) const;

	void withdraw(Company *client, double amount);

	void update() override;

	void setDepositInterestRate(double depositInterestRate) { this->depositInterestRate_ = depositInterestRate; }
	double depositInterestRate() const { return depositInterestRate_; }

	void setLoanInterestRate(double loanInterestRate) { this->loanInterestRate_ = loanInterestRate; }
	double loanInterestRate() const { return loanInterestRate_; }

private:
	std::map<Company *, BankAccount> clientMap_;

	double depositInterestRate_;

	double loanInterestRate_;
};

#endif // !BANK_H
