#ifndef ACCELERATED_CONTINUOUS_GREEDY_OPTIMIZER_H
#define ACCELERATED_CONTINUOUS_GREEDY_OPTIMIZER_H
#include"../SetFunction.h"
#include <unordered_set>
#include <random>
#include <chrono>
#include <algorithm>

class AcceleratedContinuousGreedyOptimizer
{
    public:
        std::mt19937_64 rng;
        std::uniform_real_distribution<double> unif;
	    uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	    std::seed_seq ss{uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32)};
        AcceleratedContinuousGreedyOptimizer();
        std::vector<double> maximize_fractional(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function_set> I, float epsilon=0.1);
        std::unordered_set<ll> decreasing_threshold(SetFunction &f_obj, std::vector<double> &x, float epsilon, std::unordered_set<std::unordered_set<ll>, hash_function_set> I);
        std::unordered_set<ll> pipage_rounding(SetFunction &f_obj, std::vector<double> &x, std::unordered_set<std::unordered_set<ll>, hash_function_set> I);
        std::unordered_set<ll> maximize(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function_set> I, float epsilon=0.1, bool verbose=false, bool showProgress=true, const std::vector<float>& costs=std::vector<float>());
};

#endif