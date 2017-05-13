#ifndef COMMAND_H
#define COMMAND_H

#include "Interface.h"
#include "Objects/land.h"
#include "GUI/mainwindow.h"

enum Commands {
    BUILD_BANK,
    BUILD_FACTORY,
    BUILD_FARM,
    BUILD_GARAGE,
    BUILD_MINE,
    BUILD_SUPERMARKET,
    BUILD_VILLA,
    BUY_BUILDING,
    CLOSE_AN_ACCOUNT,
    DEPOSIT,
    DISMANTLE_BUILDING,
    LOAN,
    OPEN_AN_ACCOUNT,
    REPAY,
    SELL_BUILDING,
    SHOW_DETAIL,
    WITHDRAW,
};

class ICommmand : public Interface {
public:
    virtual void execute() = 0;
};

class CommandInvoker {
public:
	void takeCommand(ICommmand *command);

	void placeCommands();

private:
	std::list<ICommmand *> commmandList_;
};

// Build structure Commands.
abstract class BuildCommand : public ICommmand {
public:
    BuildCommand(Land *building, MainWindow *mainWindow)
        : building_(building),
          mainWindow_(mainWindow) {
    }

    void execute() override = 0;

protected:
    Land *building_;
    MainWindow *mainWindow_;
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

// Sell structure command.
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

// Bank Commands.
// TODO: Finish this.
abstract class BankCommand : public ICommmand {
public:
    void execute() override = 0;

protected:

};

// Others
class ShowDetailCommand : public ICommmand {
public:
    ShowDetailCommand(MainWindow *mainWindow)
        : mainWindow_(mainWindow) {
    }

    void execute() override;

protected:
    MainWindow *mainWindow_;
};

#endif
