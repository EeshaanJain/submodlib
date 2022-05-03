#ifndef MATROID_SET_FUNCTION_H
#define MATROID_SET_FUNCTION_H
#include <unordered_set>
#include <vector>
typedef long long int ll;

class MatroidSetFunction
{
public:
    std::vector<std::vector<double>> y;
    std::vector<std::vector<double>> MatroidSetFunction::maximize(std::string optimizer, double budget, bool stopIfZeroGain, bool stopIfNegativeGain, double epsilon, bool verbose, bool showProgress, const std::vector<std::vector<double>> &costs, bool costSensitiveGreedy);
    virtual std::vector<std::vector<double>> matroidGain(std::vector<std::vector<double>> y);
    virtual std::vector<std::vector<double>> getMaxIndependenceSet(std::vector<std::vector<double>> const &w);
    virtual std::vector<std::vector<ll>> evaluateFinalSet();
};
#endif