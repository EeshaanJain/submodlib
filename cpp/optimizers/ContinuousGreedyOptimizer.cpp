
#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <utility>
#include "ContinuousGreedyOptimizer.h"

ContinuousGreedyOptimizer::ContinuousGreedyOptimizer()
{
    // std::random_device rd;
    // rng.seed(rd());
}

std::vector<std::vector<double>> ContinuousGreedyOptimizer::maximize(MatroidSetFunction &f_obj, bool verbose = false, bool showProgress = true, const std::vector<std::vector<double>> &costs = std::vector<std::vector<double>>())
{
    // std::unordered_set<ll> groundSet = f_obj.getEffectiveGroundSet();
    ll n = costs.size();
    ll m = costs[0].size();
    double t = 0;

    std::vector<std::vector<double>> w(n, std::vector<double>(m, 0));

    while (t < 1)
    {
        // std::cout << t << " && " << f_obj.delta << std::endl;
        w = f_obj.matroidGain(f_obj.y);

        // for (auto &row : w)
        // {
        //     for (auto &val : row)
        //     {
        //         std::cout << val << " ";
        //     }
        //     std::cout << std::endl;
        // }

        f_obj.getMaxIndependenceSet(w);

        t = t + f_obj.delta;
    }

    // return f_obj.evaluateFinalSet();

    return f_obj.y;
}

// std::unordered_set<ll> ContinuousGreedyOptimizer::pipage_rounding(SetFunction &f_obj, std::vector<double> &x, std::unordered_set<std::unordered_set<ll>, hash_function> I)
// {
//     std::vector<ll> T;
//     for (ll i = 0; i < x.size(); i++)
//     {
//         if (x[i] != 0 && x[i] != 1)
//         {
//             T.push_back(i);
//         }
//     }

//     try
//     {
//         while (T.size() >= 0)
//         {
//             ll i = T[0];
//             ll j = T[1];

//             if (x[i] + x[j] < 1)
//             {
//                 double p = x[j] / (x[i] + x[j]);

//                 if (unif(rng) < p)
//                 {
//                     x[j] += x[i];
//                     x[i] = 0;
//                     T.erase(T.begin() + 0);
//                 }
//                 else
//                 {
//                     x[i] += x[j];
//                     x[j] = 0;
//                     T.erase(T.begin() + 1);
//                 }
//             }
//             else
//             {
//                 double p = (1 - x[i]) / (2 - x[i] - x[j]);
//                 if (unif(rng) < p)
//                 {
//                     x[i] += x[j] - 1;
//                     x[j] = 1;
//                     T.erase(T.begin() + 1);
//                     if (x[i] == 0)
//                     {
//                         T.erase(T.begin() + 0);
//                     }
//                 }
//                 else
//                 {
//                     x[j] += x[i] - 1;
//                     x[i] = 1;
//                     T.erase(T.begin() + 0);
//                     if (x[j] == 0)
//                     {
//                         T.erase(T.begin() + 0);
//                     }
//                 }
//             }
//         }
//     }
//     catch (...)
//     {
//         std::unordered_set<ll> ground_set = f_obj.getEffectiveGroundSet();
//         ll counter = 0;
//         std::unordered_set<ll> greedy_set;
//         for (auto it : ground_set)
//         {
//             if (x[counter] == 1)
//             {
//                 greedy_set.insert(it);
//             }
//             counter++;
//         }
//         return greedy_set;
//     }
//     std::unordered_set<ll> ground_set = f_obj.getEffectiveGroundSet();
//     ll counter = 0;
//     std::unordered_set<ll> greedy_set;
//     for (auto it : ground_set)
//     {
//         if (x[counter] == 1)
//         {
//             greedy_set.insert(it);
//         }
//         counter++;
//     }
//     return greedy_set;
// }