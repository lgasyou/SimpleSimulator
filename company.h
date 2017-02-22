#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class BaseBuilding;
class BuildingManager;

class Company {
public:
    Company(const QString &name = "Xenon Inc.");

	~Company();

	// Buys building if company's money is enough:
	// Changes building's owner as this company.
	// Deducts company's cash.
    bool buy(BaseBuilding *building);

	bool purchase(double cost);

	// Changes building's owner as government's pointer.
	// Adds company's cash.
    bool sell(BaseBuilding *building);

    void update();

    inline void setTotalValue(const double totalValue) { this->totalValue_ = totalValue; }
    inline const double totalValue() const { return this->totalValue_; }

    inline void setCash(const double cash) { this->cash_ = cash; }
    inline const double cash() const { return this->cash_; }

    inline void setLiability(const double liability) { this->liability_ = liability; }
    inline const double liability() const { return this->liability_; }

    inline void setName(const QString &name) { this->name_ = name; }
    inline const QString &name() const { return this->name_; }

protected:
    QString name_;

    double cash_;

	// Records the total value of company,
	// includes the value of properties.
    double totalValue_;

    double liability_;
};

#endif // COMPANY_H
