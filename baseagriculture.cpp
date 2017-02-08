#include "baseagriculture.h"

BaseAgriculture::BaseAgriculture(const QString &type) :
	BaseBuilding("Farm", type)
{ }

BaseAgriculture::~BaseAgriculture() { }

void BaseAgriculture::update() { }
