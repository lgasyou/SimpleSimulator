#ifndef COMMAND_H
#define COMMAND_H

#include "Interface.h"

class Land;
class LegalPerson;
class MainWindow;

class ICommmand : public Interface {
public:
    virtual void execute() = 0;
    
    virtual ~ICommmand() = default;
};

// Build structure Commands.
abstract class BuildCommand : public ICommmand {
public:
    BuildCommand(Land *building)
        : building_(building) {
    }

    void execute() override = 0;

protected:
    Land *building_;
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

// Transaction command of Land.
class TransactionCommand : public ICommmand {
public:
    TransactionCommand(LegalPerson *firstParty, LegalPerson *secondParty, Land *object)
        : firstParty_(firstParty),
          secondParty_(secondParty),
          object_(object) {
    }

    void execute() override;

private:
    LegalPerson *firstParty_;
    LegalPerson *secondParty_;
    Land *object_;
};

class ShowDetailCommand : public ICommmand {
public:
    ShowDetailCommand(Land *object)
        : object_(object) {
    }

    void execute() override;

private:
    Land *object_;
};

#endif
