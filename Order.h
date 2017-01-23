#pragma once

class Industry;
class Truck;
#include <QString>

class Order {
public:
	QString item;
	double weight;
	Industry *src;
	Industry *dest;
};
