#ifndef CONTINUOUS_GREEDY_OPTIMIZER_H
#define CONTINUOUS_GREEDY_OPTIMIZER_H
#include "matroidSetFunction.h"
#include <unordered_set>
#include <random>
#include <chrono>
#include <algorithm>
#include "../utils/helper.h"

class ContinuousGreedyOptimizer
{
public:
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> unif;
    uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32)};
    ContinuousGreedyOptimizer();
    std::vector<std::vector<double>> maximize(MatroidSetFunction &f_obj, bool verbose, bool showProgress, const std::vector<std::vector<double>> &costs);
    // std::unordered_set<ll> decreasing_threshold(SetFunction &f_obj, std::vector<double> &x, double epsilon, std::unordered_set<std::unordered_set<ll>, hash_function> I);
    // std::unordered_set<ll> pipage_rounding(SetFunction &f_obj, std::vector<double> &x, std::unordered_set<std::unordered_set<ll>, hash_function> I);
};

#endif