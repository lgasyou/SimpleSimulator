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

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include "LegalPerson.h"

class Bank;

class BankAccount {
public:
    BankAccount();
    
    ~BankAccount();
    
    void update();
    
public:
    void setDebt(double debt) { this->debt_ = debt; }
    double debt() const { return debt_; }
    
    void setDeposit(double deposit) { this->deposit_ = deposit; }
    double deposit() const { return deposit_; }
    
    void setBank(Bank *bank) { this->bank_ = bank; }
    
    void setClient(LegalPerson *client) { this->client_ = client; }
    LegalPerson *client() const { return client_; }

private:
    double debt_ = 0.0;
    
    double deposit_ = 0.0;
    
    Bank *bank_ = nullptr;
    
    LegalPerson *client_ = nullptr;
};

#endif // !BANK_ACCOUNT_H
