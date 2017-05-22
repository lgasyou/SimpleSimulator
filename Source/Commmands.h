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

#ifndef COMMAND_H
#define COMMAND_H

#include <unordered_set>
#include "Interface.h"

class LandParcel;
class LegalPerson;

class QWidget;

class ICommand : public Interface {
public:
    virtual void execute() = 0;
    
    virtual ~ICommand() = default;
};

class WriteCommand : public ICommand {
public:
    WriteCommand(QWidget *caller) {
        cachedWidgets_.insert(caller);
    }

    void execute() override;

private:
    static std::unordered_set<QWidget *> cachedWidgets_;
};

class ReadCommand : public ICommand {
public:
    using ICommand::ICommand;

    void execute() override = 0;
};

// Build structure Commands.
abstract class BuildCommand : public WriteCommand {
public:
    BuildCommand(QWidget *caller, LandParcel *building)
        : WriteCommand(caller),
          building_(building) {
    }

    void execute() override = 0;

protected:
    LandParcel *building_;
};

class BuildBank : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildFactory : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildFarm : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildGarage : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildMine : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildSupermarket : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class BuildVilla : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

class DismantleBuilding : public BuildCommand {
public:
    using BuildCommand::BuildCommand;

    void execute() override;
};

// Transaction command of LandParcel.
class TransactionCommand : public WriteCommand {
public:
    TransactionCommand(QWidget *caller, LegalPerson *firstParty, LegalPerson *secondParty, LandParcel *object)
        : WriteCommand(caller),
          firstParty_(firstParty),
          secondParty_(secondParty),
          object_(object) {
    }

    void execute() override;

private:
    LegalPerson *firstParty_;
    LegalPerson *secondParty_;
    LandParcel *object_;
};

class ShowDetailCommand : public ReadCommand {
public:
    ShowDetailCommand(LandParcel *object)
        : object_(object) {
    }

    void execute() override;

private:
    LandParcel *object_;
};

#endif
