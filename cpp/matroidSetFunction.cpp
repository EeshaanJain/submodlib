
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include "MatroidSetFunction.h"
#include "optimizers/ContinuousGreedyOptimizer.h"

std::vector<std::vector<double>> MatroidSetFunction::maximize(std::string optimizer, double delta, bool stopIfZeroGain, bool stopIfNegativeGain, double epsilon, bool verbose, bool showProgress, const std::vector<std::vector<double>> &costs, bool costSensitiveGreedy)
{

    if (optimizer == "ContinuousGreedy")
    {
        return ContinuousGreedyOptimizer().maximize(*this, delta, epsilon, verbose, showProgress, costs);
    }
    else
    {
        std::cout << "Invalid Optimizer" << std::endl;
    }
}