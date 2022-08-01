#include "UniformDistribution.h"

UniformDistribution::UniformDistribution(double mean, double stddev) :
    twister{std::random_device{}()}, ud{mean, stddev} {}

double UniformDistribution::next() {
    return ud(twister);
}