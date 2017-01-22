#ifndef VALUEGENERATOR_H
#define VALUEGENERATOR_H

#include <random>

class ValueGenerator {
public:
    ValueGenerator();

    static int uniformDistribution(int lowerBound, int upperBound);

    static double normalDistribution(double mu, double sigma);

private:
    static std::default_random_engine generator_;
};

#endif // VALUEGENERATOR_H
