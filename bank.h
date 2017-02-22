#ifndef BANK_H
#define BANK_H

#include "basefinance.h"

class Bank : public BaseFinance {
public:
	Bank(const QString &name);
};

#endif // !BANK_H
