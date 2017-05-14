/*
 *  Copyright 2017 Li Zeqing
 *  
 *  This file is part of World Simulator.
 *  
 *  World Simulator is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  World Simulator is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with World Simulator. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BANK_H
#define BANK_H

#include <map>
#include <QString>

#include "basefinance.h"
#include "bankaccount.h"
#include "legalperson.h"

class Bank : public BaseFinance {
public:
    Bank(const QString &name = "Bank");
    
    ~Bank();
    
    void init();
    
    void closeAnAccount(LegalPerson *client);
    
    void deposit(LegalPerson *client, double amount);
    
    void loan(LegalPerson *client, double amount);
    
    void openAnAccount(LegalPerson *client);
    
    void repay(LegalPerson *client, double amount);
    
    const BankAccount &accountOf(LegalPerson *client) const;
    
    void withdraw(LegalPerson *client, double amount);
    
    void update() override;

public:    
    void setDepositInterestRate(double depositInterestRate) { this->depositInterestRate_ = depositInterestRate; }
    double depositInterestRate() const { return depositInterestRate_; }
    
    void setLoanInterestRate(double loanInterestRate) { this->loanInterestRate_ = loanInterestRate; }
    double loanInterestRate() const { return loanInterestRate_; }

private:
    std::map<LegalPerson *, BankAccount> clientMap_;
    
    double depositInterestRate_;
    
    double loanInterestRate_;
};

inline void Bank::init() {
    depositInterestRate_ = 0.003;
    loanInterestRate_ = 0.008;
}

inline void Bank::closeAnAccount(LegalPerson *client) {
    const BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() + bankAccount.deposit() - bankAccount.debt();
    if (finalCash >= 0) {
        client->setCash(finalCash);
        clientMap_.erase(client);
    }
}

inline void Bank::deposit(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() - amount;
    double finalDeposit = bankAccount.deposit() + amount;
    bankAccount.setDeposit(finalDeposit);
    client->setCash(finalCash);
}

inline void Bank::loan(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() + amount;
    double finalDebt = bankAccount.debt() + amount;
    bankAccount.setDeposit(finalDebt);
    client->setCash(finalCash);
}

inline void Bank::openAnAccount(LegalPerson *client) {
    clientMap_[client].setBank(this);
}

inline void Bank::repay(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() - amount;
    double finalDebt = bankAccount.debt() - amount;
    bankAccount.setDeposit(finalDebt);
    client->setCash(finalCash);
}

inline const BankAccount &Bank::accountOf(LegalPerson *client) const {
    return clientMap_.find(client)->second;
}

inline void Bank::withdraw(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() + amount;
    double finalDeposit = bankAccount.deposit() - amount;
    bankAccount.setDeposit(finalDeposit);
    client->setCash(finalCash);
}

#endif // !BANK_H
