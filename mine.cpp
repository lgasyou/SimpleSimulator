#include "mine.h"

#include <QString>

Mine::Mine(const QString &name, const QString &mineType) :
	BaseIndustry(name, "Mine"),
	mineType_(mineType)
{ }
