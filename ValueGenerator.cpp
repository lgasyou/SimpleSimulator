#include "ValueGenerator.h"
#include <ctime>

ValueGenerator &ValueGenerator::instance() {
	static ValueGenerator valueGenerator;
	return valueGenerator;
}

int ValueGenerator::uniformDistribution(int lowerBound, int upperBound) {
    std::uniform_int_distribution<int> range(lowerBound, upperBound);
    return range(generator_);
}

double ValueGenerator::normalDistribution(double mu, double sigma) {
    std::normal_distribution<double> range(mu, sigma);
    return range(generator_);
}

std::default_random_engine ValueGenerator::generator_ =
        std::default_random_engine(static_cast<unsigned>(time(nullptr)));
