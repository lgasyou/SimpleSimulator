#ifndef BASEBUILDING_H
#define BASEBUILDING_H

#include <QString>
class Company;

/*	the base of building classes.
	three types of building:
	* Residence,
	* Commerce,
	* Factory.
*/
class BuildingBase {
public:
    static const int numberOfProperties = 4;

    BuildingBase(double value);
    BuildingBase(const QString &name, double value, const QString &type, Company *owner, double deltaValue = 0);

    BuildingBase(const BuildingBase &);

    virtual ~BuildingBase() { }

	// manual manage building
    virtual void manage(const QString &);
	
	// updates data after each turn
	virtual void update();

	void changeBaseValue();

    inline void setValue(double value) { this->value_ = value; }
	inline const double value() const { return this->value_; }

    inline void setDeltaValue(double deltaValue) { this->deltaValue_ = deltaValue; }
    inline const double deltaValue() const { return this->deltaValue_; }

    inline void setName(const QString &name) { this->name_ = name; }
    inline const QString &name() const { return this->name_; }

    inline void setType(const QString &type) { this->type_ = type; }
    inline const QString &type() const { return this->type_; }

    inline void setOwner(Company *const owner) { this->owner_ = owner; }
    inline Company *const owner() const { return this->owner_; }

private:
    QString name_;
    double value_;
    double deltaValue_;
    QString type_;
    Company *owner_;
};

#endif // BASEBUILDING_H
