#include "basetransportation.h"

#include <QString>

BaseTransportation::BaseTransportation(const QString &name, const QString &type) :
	BaseBuilding(name, type)
{ }

BaseTransportation::~BaseTransportation() { }