#ifndef ORDER_H
#define ORDER_H

#include <QString>

class Industry;
class Truck;

struct Order {
	Order(const QString &_goods, double _weight, Industry *_dest, Industry *_src);

	QString goods;
	double weight;
	Industry *dest;
	Industry *src;
};

#endif // !ORDER_H