#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<utility>
#include"AcceleratedContinuousGreedyOptimizer.h"
#include"../utils/helper.h"

AcceleratedContinuousGreedyOptimizer::AcceleratedContinuousGreedyOptimizer(){
    rng.seed(ss);
}

std::unordered_set<ll> AcceleratedContinuousGreedyOptimizer::decreasing_threshold(SetFunction &f_obj, std::vector<double> &x, double epsilon, std::unordered_set<std::unordered_set<ll>, hash_function> I) {
    std::unordered_set<ll> B;
    std::unordered_set<ll> groundSet = f_obj.getEffectiveGroundSet();
    ll n = groundSet.size();
    double d = -1 * std::numeric_limits<double>::max();
    for (auto it = groundSet.begin(); it != groundSet.end(); it++)
    {
        std::unordered_set<ll> curr = {*it};
        d = std::max(d, f_obj.evaluate(curr));
    }
    ll r = matroid_rank(I);
    double w = d;
    ll num_samples = r * (ll) std::log(n) / (epsilon * epsilon);
    while(w >= epsilon * d / r)
    {
        for (auto e : groundSet)
        {
            double w_e = 0;
            std::unordered_set R_x_B = R(x, B, groundSet, epsilon, rng, unif);
            for (ll i = 0; i < num_samples; i++)
            {
                w_e += f_obj.marginalGainWithMemoization(R_x_B, e, false);
            }
            w_e = w_e / num_samples;
            std::unordered_set<ll> curr = {e};
            std::unordered_set B_e(B);
            B_e.insert(curr.begin(), curr.end());
            if (I.find(B_e) != I.end() && w_e >= w)
            {
                B.insert(e);
            }
            w = w *(1 - epsilon);
        }
    }
    return B;
}

std::vector<double> AcceleratedContinuousGreedyOptimizer::maximize_fractional(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function> I, float epsilon=0.1)
{
    std::unordered_set<ll> groundSet = f_obj.getEffectiveGroundSet();
    ll n = groundSet.size();
    std::vector<double> x(n, 0);
    double t = epsilon;

    while (t <= 1)
    {
        std::unordered_set<ll> B = decreasing_threshold(f_obj, x, epsilon, I);
        for (auto it : B)
	    {
		    ll idx = get_index(groundSet, it);
		    x[idx] += epsilon;
	    }
        t = t + epsilon;
    }
    return x;
}

std::unordered_set<ll>  AcceleratedContinuousGreedyOptimizer::pipage_rounding(SetFunction &f_obj, std::vector<double> &x, std::unordered_set<std::unordered_set<ll>, hash_function> I)
{
    std::vector<ll> T;
    for (ll i = 0; i < x.size(); i++)
    {
        if (x[i] != 0 && x[i] != 1)
        {
            T.push_back(i);
        }
    }

    try
    {
        while (T.size() >= 0)
        {
            ll i = T[0];
            ll j = T[1];

            if (x[i] + x[j] < 1)
            {
                double p = x[j] / (x[i] + x[j]);

                if (unif(rng) < p)
                {
                    x[j] += x[i];
                    x[i] = 0;
                    T.erase(T.begin() + 0);
                }
                else
                {
                    x[i] += x[j];
                    x[j] = 0;
                    T.erase(T.begin() + 1);
                }
            }
            else
            {
                double p = (1 - x[i]) / (2 - x[i] - x[j]);
                if (unif(rng) < p)
                {
                    x[i] += x[j] - 1;
                    x[j] = 1;
                    T.erase(T.begin() + 1);
                    if (x[i] == 0)
                    {
                        T.erase(T.begin() + 0);
                    }
                }
                else
                {
                    x[j] += x[i] - 1;
                    x[i] = 1;
                    T.erase(T.begin() + 0);
                    if (x[j] == 0)
                    {
                        T.erase(T.begin() + 0);
                    }
                }
            }
        }
    }
    catch(...)
    {
        std::unordered_set<ll> ground_set = f_obj.getEffectiveGroundSet();
        ll counter = 0;
        std::unordered_set<ll> greedy_set;
        for (auto it : ground_set)
        {
            if (x[counter] == 1)
            {
                greedy_set.insert(it);
            }
            counter++;
        }
        return greedy_set;
    }
    std::unordered_set<ll> ground_set = f_obj.getEffectiveGroundSet();
    ll counter = 0;
    std::unordered_set<ll> greedy_set;
    for (auto it : ground_set)
    {
        if (x[counter] == 1)
        {
            greedy_set.insert(it);
        }
        counter++;
    }
    return greedy_set;
}

std::unordered_set<ll> AcceleratedContinuousGreedyOptimizer::maximize(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function> I, float epsilon=0.1, bool verbose=false, bool showProgress=true, const std::vector<float>& costs=std::vector<float>())
{
    std::vector<double> x = maximize_fractional(f_obj, I, epsilon);
    std::unordered_set<ll> greedySet = pipage_rounding(f_obj, x, I);
    return greedySet;
}