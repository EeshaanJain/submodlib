
#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include <string>
#include "matroidSetFunction.h"
#include "./optimizers/ContinuousGreedyOptimizer.h"

std::vector<std::vector<double>> MatroidSetFunction::matroidGain(std::vector<std::vector<double>> y) {}
std::vector<std::vector<double>> MatroidSetFunction::getMaxIndependenceSet(std::vector<std::vector<double>> const &w) {}
std::vector<std::vector<ll>> MatroidSetFunction::evaluateFinalSet() {}

std::vector<std::vector<double>> MatroidSetFunction::maximize(std::string optimizer, bool verbose, bool showProgress, const std::vector<std::vector<double>> &costs)
{

    if (optimizer == "ContinuousGreedy")
    {
        return ContinuousGreedyOptimizer().maximize(*this, verbose, showProgress, costs);
    }
    else
    {
        std::cout << "Invalid Optimizer" << std::endl;
        std::vector<std::vector<double>> empty = std::vector<std::vector<double>>();
        return empty;
    }
}