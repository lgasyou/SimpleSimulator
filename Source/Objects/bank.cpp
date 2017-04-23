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

#include "bank.h"

Bank::Bank(const QString &name) :
    BaseFinance(name, "Bank")
{ }

Bank::~Bank() { }

void Bank::init() {
    depositInterestRate_ = 0.003;
    loanInterestRate_ = 0.008;
}

void Bank::closeAnAccount(LegalPerson *client) {
    const BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() + bankAccount.deposit() - bankAccount.debt();
    if (finalCash >= 0) {
        client->setCash(finalCash);
        clientMap_.erase(client);
    }
}

void Bank::deposit(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() - amount;
    double finalDeposit = bankAccount.deposit() + amount;
    bankAccount.setDeposit(finalDeposit);
    client->setCash(finalCash);
}

void Bank::loan(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() + amount;
    double finalDebt = bankAccount.debt() + amount;
    bankAccount.setDeposit(finalDebt);
    client->setCash(finalCash);
}

void Bank::openAnAccount(LegalPerson *client) {
    clientMap_[client].setBank(this);
}

void Bank::repay(LegalPerson *client, double amount) {
    BankAccount &bankAccount = clientMap_[client];
    double finalCash = client->cash() - amount;
    double finalDebt = bankAccount.debt() - amount;
    bankAccount.setDeposit(finalDebt);
    client->setCash(finalCash);
}

const BankAccount &Bank::accountOf(LegalPerson *client) const {
    return clientMap_.find(client)->second;
}

void Bank::withdraw(LegalPerson *client, double amount) {
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