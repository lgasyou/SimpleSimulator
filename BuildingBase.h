#ifndef BUILDINGBASE_H
#define BUILDINGBASE_H

#include <QString>

class Company;

//	the base of building classes.
//	three types of building:
//	* Residence,
//	* Commerce,
//	* Industry.
class BuildingBase {
public:
	BuildingBase(const QString &name = "Foundation", const QString &type = "Foundation",
		Company *owner = nullptr, double deltaValue = 0.0);

    BuildingBase(const BuildingBase &, const QString &);

    virtual ~BuildingBase() { }

	void initBasicValue();

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

#endif // BUILDINGBASE_H