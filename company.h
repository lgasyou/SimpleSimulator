#ifndef COMPANY_H
#define COMPANY_H

#include <QString>

class BaseBuilding;

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

    void setCash(const double cash) { this->cash_ = cash; }
    double cash() const { return this->cash_; }

    void setLiability(const double liability) { this->liability_ = liability; }
    double liability() const { return this->liability_; }

    void setName(const QString &name) { this->name_ = name; }
    const QString &name() const { return this->name_; }

	void setTotalValue(const double totalValue) { this->totalValue_ = totalValue; }
	double totalValue() const { return this->totalValue_; }

protected:
    double cash_ = 1000.0;

    double liability_ = 0.0;

    QString name_;

	// Records the total value of company,
	// includes the value of properties.
    double totalValue_ = 1000.0;
};

#endif // COMPANY_H
