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

#ifndef COMPANY_H
#define COMPANY_H

#include "basebuilding.h"
#include "legalperson.h"

class Company : public LegalPerson {
public:
    Company(const QString &name = "Xenon Inc.");

    ~Company();

    // Buys building if company's money is enough:
    // Changes building's owner as this company.
    // Deducts company's cash.
    bool phrchase(BaseBuilding *building);

    // Changes building's owner as government's pointer.
    // Adds company's cash.
    bool sell(BaseBuilding *building);

    virtual void update() override;

};

#endif // COMPANY_H
