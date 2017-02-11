#ifndef VALUEGENERATOR_H
#define VALUEGENERATOR_H

#include <random>

class ValueGenerator {
public:
	static ValueGenerator &instance();

    int uniformDistribution(int lowerBound, int upperBound);

    double normalDistribution(double mu, double sigma);

private:
	ValueGenerator() { }

	~ValueGenerator() { }

	ValueGenerator(const ValueGenerator &) = delete;

	ValueGenerator &operator=(const ValueGenerator &) = delete;

private:
    static std::default_random_engine generator_;
};

#endif // VALUEGENERATOR_H
