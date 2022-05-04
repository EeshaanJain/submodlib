#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>
#include <map>
#include <random>
#include "Sap.h"

Sap::Sap() {}

// Constructor for dense mode (kenel supplied)

// For cluster mode
Sap::Sap(std::vector<std::vector<double>> costs, std::vector<std::vector<std::unordered_set<ll>>> input_feasible_set)
{
    m = costs.size();
    n = costs[0].size();

    delta = 1.0 / (9.0 * n * n);

    // Initialize the cost matrix
    cost = costs;

    // initialise y
    for (ll i = 0; i < n; i++)
    {
        y.push_back(std::vector<double>((int)input_feasible_set[i].size(), 0));
    }

    feasible_set = input_feasible_set;

    // initialise item_set

    for (int i = 0; i < m; i++)
    {
        std::unordered_set<std::pair<ll, ll>, pair_hash> temp;
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < (int)feasible_set[j].size(); k++)
            {
                if (feasible_set[j][k].find(i) != feasible_set[j][k].end())
                {
                    temp.insert(std::make_pair(j, k));
                }
            }
        }
        item_set.push_back(temp);
    }

    // std::cout << "constructer created" << std::endl;
}

std::vector<std::vector<double>> Sap::getMaxIndependenceSet(std::vector<std::vector<double>> const &w)
{

    for (int j = 0; j < n; j++)
    {
        // std::cout << "entry j: " << j << std::endl;
        double max_so_far = 0;
        int max_so_far_index = 0;

        for (int i = 0; i < (int)feasible_set[j].size(); i++)
        {
            double score = 0;
            for (auto elem : feasible_set[j][i])
            {
                score += w[j][elem];
            }

            if (score >= max_so_far)
            {
                max_so_far = score;
                max_so_far_index = i;
            }
        }

        y[j][max_so_far_index] += delta;
    }

    return y;
}

std::vector<std::vector<double>> Sap::matroidGain(std::vector<std::vector<double>> y)
{
    std::vector<std::vector<double>> w(n, std::vector<double>(m, 0));

    ll num_samples = std::pow(m * n, 5);

    for (ll i = 0; i < num_samples; i++)
    {
        std::unordered_set<std::pair<ll, ll>, pair_hash> R_t(n);

        for (int jj = 0; jj < n; jj++)
        {
            for (int k = 0; k < (int)feasible_set[jj].size(); k++)
            {
                std::uniform_real_distribution<double> unif;
                double sample = unif(rng);
                if (sample < y[jj][k])
                {
                    R_t.insert(std::make_pair(jj, k));
                }
            }
        }

        // std::cout << "sampling success " << i << std::endl;

        for (int e = 0; e < m; e++)
        {
            for (ll j = 0; j < n; j++)
            {
                double opt = 0;

                // std::cout << "idhar " << e << std::endl;

                for (auto p : item_set[e])
                {
                    // std::cout << "here " << p.first << " " << p.second << std::endl;
                    if (R_t.find(p) != R_t.end())
                    {
                        // std::cout << p.first << std::endl;
                        opt = std::max(opt, cost[e][p.first]);
                    }
                }

                w[j][e] = std::max(0.0, cost[e][j] - opt);
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            w[i][j] /= num_samples;
        }
    }

    return w;
}

std::vector<std::vector<ll>> Sap::evaluateFinalSet()
{
    std::vector<std::vector<ll>> final_set;
    for (int i = 0; i < m; i++)
    {
        final_set.push_back(std::vector<ll>{i, -1});
    }
    for (int i = 0; i < n; i++)
    {
        std::uniform_real_distribution<double> unif;
        double sample = unif(rng);

        int score = 0;

        int k = 0;
        while ((k < (int)y[i].size() - 1) && score + y[i][k] < sample)
        {
            score += y[i][k];
            k++;
        }

        // std::cout << i << " " << k << " " << sample << std::endl;
        // std::cout << (int)y[0].size() << " " << (int)y[1].size() << std::endl;

        for (auto e : feasible_set[i][k])
        {
            if (cost[e][i] > final_set[e][1])
            {
                final_set[e][0] = i;
                final_set[e][1] = cost[e][i];
            }
        }
    }

    return final_set;
}