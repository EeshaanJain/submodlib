#ifndef SAP_H
#define SAP_H

#include "ContinuousGreedyOptimizer.h"
#include "matroidSetFunction.h"
#include <unordered_set>
#include <vector>

class Sap : public MatroidSetFunction
{
protected:
    ll n; // size of ground set
    ll m; // size of master set
    std::vector<std::vector<double>> cost;
    std::mt19937_64 rng;
    std::vector<std::vector<std::unordered_set<ll>>> feasible_set;
    std::vector<std::unordered_set<std::pair<ll, ll>, pair_hash>> item_set;
    // std::set<std::pair<ll, std::set<ll>>> groundset;

public:
    Sap();

    Sap(std::vector<std::vector<double>> cost, std::vector<std::vector<std::unordered_set<ll>>> feasible_set);

    std::vector<std::vector<double>> matroidGain(std::vector<std::vector<double>> y);
    std::vector<std::vector<double>> getMaxIndependenceSet(std::vector<std::vector<double>> const &w);
    std::vector<std::vector<ll>> evaluateFinalSet();
};

#endif
