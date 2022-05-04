#ifndef SWP_H
#define SWP_H

#include "ContinuousGreedyOptimizer.h"
#include "matroidSetFunction.h"
#include <unordered_set>
#include <vector>

class Swp : public MatroidSetFunction
{
protected:
    ll n; // size of ground set
    ll m; // size of master set
    std::vector<std::vector<double>> cost;
    std::mt19937_64 rng;

public:
    Swp();

    Swp(std::vector<std::vector<double>> cost, ll groundSetSize);

    std::vector<std::vector<double>> matroidGain(std::vector<std::vector<double>> y);
    std::vector<std::vector<double>> getMaxIndependenceSet(std::vector<std::vector<double>> const &w);
    std::vector<std::vector<ll>> evaluateFinalSet();
};

#endif
