#ifndef MATROID_SET_FUNCTION_H
#define MATROID_SET_FUNCTION_H
#include <unordered_set>
#include <vector>
typedef long long int ll;

class MatroidSetFunction
{
public:
    double delta;
    std::vector<std::vector<double>> y;
    std::vector<std::vector<double>> maximize(std::string optimizer, bool verbose, bool showProgress, const std::vector<std::vector<double>> &costs);
    virtual std::vector<std::vector<double>> matroidGain(std::vector<std::vector<double>> y);
    virtual std::vector<std::vector<double>> getMaxIndependenceSet(std::vector<std::vector<double>> const &w);
    virtual std::vector<std::vector<ll>> evaluateFinalSet();
};
#endif