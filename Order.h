#ifndef ORDER_H
#define ORDER_H

class Industry;
class Truck;
#include <QString>

struct Order {
	Order(const QString &_goods, double _weight, Industry *_dest, Industry *_src);

	QString goods;
	double weight;
	Industry *dest;
	Industry *src;
};

#endif // !ORDER_H