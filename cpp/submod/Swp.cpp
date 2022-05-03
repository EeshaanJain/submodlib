#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>
#include <map>
#include <random>
#include "../utils/helper.h"
#include "Swp.h"

Swp::Swp() {}

// Constructor for dense mode (kenel supplied)

// For cluster mode
Swp::Swp(std::vector<std::vector<double>> costs)
{
    n = costs.size();
    m = costs[0].size();

    delta = 1 / (9 * m * m);

    // Initialize the cost matrix
    cost = costs;

    y = std::vector<std::vector<double>>(n, std::vector<double>(m, 0));
}

std::vector<std::vector<double>> Swp::getMaxIndependenceSet(std::vector<std::vector<double>> const &w)
{
    std::vector<std::pair<ll, ll>> g;

    for (int j = 0; j < m; j++)
    {
        int opt = 0;
        double opt_max = 0;
        for (int i = 0; i < n; i++)
        {
            opt_max = std::max(opt_max, w[i][j]);
            if (w[i][j] == opt_max)
            {
                opt = i;
            }
        }

        g.push_back(std::make_pair(opt, j));
    }

    for (auto p : g)
    {
        y[p.first][p.second] += delta;
    }

    return y;
}

std::vector<std::vector<double>> Swp::matroidGain(std::vector<std::vector<double>> y)
{
    std::vector<std::vector<double>> w(n, std::vector<double>(m, 0));

    ll num_samples = (1 + std::log(n)) * 10 / (delta * delta);

    for (int e = 0; e < n; e++)
    {
        for (ll j = 0; j < m; j++)
        {
            double w_e = 0;
            for (ll i = 0; i < num_samples; i++)
            {
                std::unordered_set<ll> R;
                for (ll jj = 0; jj < m; jj++)
                {
                    std::uniform_real_distribution<double> unif;
                    double sample = unif(rng);
                    if (sample < y[e][jj])
                    {
                        R.insert(jj);
                    }
                }

                double gain = 0;
                if (R.find(j) == R.end())
                {
                    gain = cost[e][j];
                }
                w_e += gain;
            }
            w_e = w_e / num_samples;
            w[e][j] = w_e;
        }
    }

    // double gain = 0;
    // if (R.find(item) == R.end())
    // {
    //     gain = cost[e][item];
    // }

    return w;
}

std::vector<std::vector<ll>> Swp::evaluateFinalSet()
{
    std::vector<std::vector<ll>> final_set;
    for (int i = 0; i < m; i++)
    {
        std::uniform_real_distribution<double> unif;
        double sample = unif(rng);

        int score = 0;

        int k = 0;
        while (score + y[k][i] < sample)
        {
            score += y[k][i];
            k++;
        }

        final_set.push_back(std::vector<ll>{k, i});
    }
}