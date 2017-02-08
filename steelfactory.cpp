#include "steelfactory.h"
#include "warehouse.h"
#include "goods.h"

#include "industrychainmanager.h"

SteelFactory::SteelFactory() :
	BaseIndustry("Steel Factory")
{ 
	const QString &product = "Steel";
	products_.push_back(Goods(product, 1));
	rawMaterials_ = IndustryChainManager::instance().precursors(product);
}

SteelFactory::~SteelFactory() { }