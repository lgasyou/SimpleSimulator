#ifndef PRICEMANAGER_H
#define PRICEMANAGER_H

class QString;

// This class is designed for controling the price of goods in the game.
// It adjusts the prices dynamiclly according to the supply-demand
// relationship.
class PriceManager {
public:
	static PriceManager &instance();

	void readFile(const QString &);
	
	void update();

private:
	PriceManager();
	~PriceManager();
	PriceManager(const PriceManager &) = delete;
	PriceManager &operator=(const PriceManager &) = delete;
};

#endif // !PRICEMANAGER_H

