#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include "basecommerce.h"

class QString;

class Supermarket : public BaseCommerce {
public:
	Supermarket(const QString &name = "Supermarket");
};

#endif // !SUPERMARKET_H
