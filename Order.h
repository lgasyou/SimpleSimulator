#pragma once

class Industry;
class Truck;
#include <QString>

class Order {
public:
	QString goods;
	double weight;
	Industry *src;
	Industry *dest;
};
