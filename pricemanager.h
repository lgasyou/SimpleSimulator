#ifndef PRICEMANAGER_H
#define PRICEMANAGER_H

#include <vector>
#include <QString>

struct PriceItem {
public:
	PriceItem::PriceItem(const QString &name_, const QString &unit_, double price_) :
		name(name_),
		unit(unit_),
		price(price_) { }

public:
	QString name;

	QString unit;

	double price;
};



// This class is designed for controlling the price of goods in the game.
// It adjusts the prices dynamiclly according to the supply-demand
// relationship.
class PriceManager {
public:
	// Use singleton pattern.
	static PriceManager &instance();
	
	double price(const QString &name) const;

	// Updates the prices of all goods.
	void update();

private:
	// Hide constructor and destructor.
	PriceManager();

	~PriceManager();

	void init();

	PriceManager(const PriceManager &) = delete;

	PriceManager &operator=(const PriceManager &) = delete;

private:
	std::vector<PriceItem> prices_;
};

#endif // !PRICEMANAGER_H

