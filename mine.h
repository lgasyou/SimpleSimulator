#ifndef MINE_H
#define MINE_H

#include "baseindustry.h"

class QString;

class Mine : public BaseIndustry {
public:
	Mine(const QString &name = "Mine", const QString &mineType = "Coal");

	const QString &mineType() const { return this->mineType_; }

private:
	QString mineType_;
};

#endif // !MINE_H
