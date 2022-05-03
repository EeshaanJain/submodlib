#ifndef SWP_H
#define SWP_H

#include "../optimizers/NaiveGreedyOptimizer.h"
#include "../optimizers/LazyGreedyOptimizer.h"
#include "../optimizers/StochasticGreedyOptimizer.h"
#include "../optimizers/LazierThanLazyGreedyOptimizer.h"
#include "../matroidSetFunction.h"
#include "../utils/sparse_utils.h"
#include <unordered_set>
#include <vector>

class Swp : public MatroidSetFunction
{
protected:
    ll n; // size of ground set
    ll m; // size of master set
    std::vector<std::vector<double>> cost;
    double delta;
    std::mt19937_64 rng;

public:
    Swp();

    Swp(std::vector<std::vector<double>> cost);

    std::vector<std::vector<double>> matroidGain(std::vector<std::vector<double>> y);
    std::vector<std::vector<double>> getMaxIndependenceSet(std::vector<std::vector<double>> const &w);
    std::vector<std::pair<ll, ll>> evaluateFinalSet();
};

#endif
