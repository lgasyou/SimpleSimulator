#include "baseagriculture.h"

BaseAgriculture::BaseAgriculture(const QString &name, const QString &type) :
	BaseBuilding(name, type)
{ }

BaseAgriculture::~BaseAgriculture() { }

void BaseAgriculture::update() { }
