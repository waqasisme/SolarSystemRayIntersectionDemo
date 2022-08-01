#ifndef __UNIFORMDISTRIBUTION_H__
#define __UNIFORMDISTRIBUTION_H__

#include <random>

class UniformDistribution {
public:
    UniformDistribution(double mean, double stddev);

    double next();

private:
    std::mt19937 twister;
    std::uniform_real_distribution<> ud;
};

#endif // __UNIFORMDISTRIBUTION_H__
