#include<iostream>
#include<set>
#include<vector>
#include<string>
#include<algorithm>
#include<cmath>
#include<utility>
#include"AcceleratedContinuousGreedyOptimizer.h"

AcceleratedContinuousGreedyOptimizer::AcceleratedContinuousGreedyOptimizer(){
    rng.seed(ss);
}

ll matroid_rank(std::unordered_set<std::unordered_set<ll>, hash_function_set> &I)
{
	ll rank = 0;
	for (auto independent_set : I)
	{
		// std::cout << independent_set.size() << " ";
        rank = std::max(rank, (ll)independent_set.size());
	}
    // std::cout << " $6\n";
	return rank;
}

ll matroid_rank(std::unordered_set<ll> &S, std::unordered_set<std::unordered_set<ll>, hash_function_set> &I)
{
	ll rank = 0;
	for (auto independent_set : I)
	{
		if (std::includes(S.begin(), S.end(), independent_set.begin(), independent_set.end()))
		{
			rank = std::max(rank, (ll)independent_set.size());
		}
	}
	return rank;
}

ll get_index(std::unordered_set<ll> &s, ll k)
{
	ll idx = 0;
	for (auto u : s)
	{

		if (u == k)
			return idx;

		idx++;
	}
	return -1;
}


std::unordered_set<ll> R(std::vector<double> x, std::unordered_set<ll> S, std::unordered_set<ll> &groundSet, float eps, std::mt19937_64 rng, std::uniform_real_distribution<double> unif)
{
	std::vector<double> probs = x;
	for (auto it : S)
	{
		ll idx = get_index(groundSet, it);
		probs[idx] += eps;
        // std::cout << probs[idx] << " ";
	}
    // std::cout << " $8\n";

	std::unordered_set<ll> sampled_set;
	ll counter = 0;
	for (auto it : groundSet)
	{
		// std::cout << unif(rng) << " ";
        if (unif(rng) <= probs[get_index(groundSet, it)])
		{
			sampled_set.insert(it);
            // std::cout << it << " ";
		}
		counter++;
	}
    // std::cout << " $7\n";
	return sampled_set;
}

std::unordered_set<ll> AcceleratedContinuousGreedyOptimizer::decreasing_threshold(SetFunction &f_obj, std::vector<double> &x, float epsilon, std::unordered_set<std::unordered_set<ll>, hash_function_set> I) {
    std::unordered_set<ll> B;
    std::unordered_set<ll> groundSet = f_obj.getEffectiveGroundSet();
    ll n = groundSet.size();
    double d = std::numeric_limits<double>::min();
    for (auto it : groundSet)
    {
        std::unordered_set<ll> curr = {it};
        d = std::max(d, f_obj.evaluate(curr));
    }
    ll r = matroid_rank(I);
    double w = d;
    ll num_samples = r * (ll) std::log(n) / (epsilon * epsilon);
    // std::cout << epsilon * d / r << " " << w << " $5\n";
    while(w >= epsilon * d / r)
    {
        for (auto e : groundSet)
        {
            double w_e = 0;
            for (ll i = 0; i < num_samples; i++)
            {
                std::unordered_set<ll> R_x_B = R(x, B, groundSet, epsilon, rng, unif);
                w_e += f_obj.marginalGain(R_x_B, e);
            }
            w_e = w_e * 1.0 / num_samples;
            std::unordered_set<ll> B_e = B;
            B_e.insert(e);
            if (I.find(B_e) != I.end() && w_e >= w)
            {
                B.insert(e);
            }
            w = w *(1 - epsilon);
        }
    }
    return B;
}

std::vector<double> AcceleratedContinuousGreedyOptimizer::maximize_fractional(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function_set> I, float epsilon)
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
		    // std::cout << it << " ";
            ll idx = get_index(groundSet, it);
		    x[idx] += epsilon;
	    }
        // std::cout << " $4\n";
        t = t + epsilon;
    }
    return x;
}

std::unordered_set<ll>  AcceleratedContinuousGreedyOptimizer::pipage_rounding(SetFunction &f_obj, std::vector<double> &x, std::unordered_set<std::unordered_set<ll>, hash_function_set> I)
{
    std::vector<ll> T;
    for (ll i = 0; i < x.size(); i++)
    {
        // std::cout << x[i] << " ";
        if (x[i] > 0 && x[i] < 1)
        {
            T.push_back(i);
        }
    }
    // std::cout << " $3\n" << T.size() << " $1\n";
    // for (auto it:T)
    // {
    //     std::cout << it << " ";
    // }
    // std::cout << " $2\n";
    try
    {
        while (T.size() > 0)
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
                    T.erase(std::find(T.begin(), T.end(), i));
                }
                else
                {
                    x[i] += x[j];
                    x[j] = 0;
                    T.erase(std::find(T.begin(), T.end(), j));
                }
            }
            else
            {
                double p = (1 - x[i]) / (2 - x[i] - x[j]);
                if (unif(rng) < p)
                {
                    x[i] += x[j] - 1;
                    x[j] = 1;
                    T.erase(std::find(T.begin(), T.end(), j));
                    if (x[i] == 0)
                    {
                        T.erase(std::find(T.begin(), T.end(), i));
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

std::unordered_set<ll> AcceleratedContinuousGreedyOptimizer::maximize(SetFunction &f_obj, std::unordered_set<std::unordered_set<ll>, hash_function_set> I, float epsilon, bool verbose, bool showProgress, const std::vector<float>& costs)
{
    std::vector<double> x = maximize_fractional(f_obj, I, epsilon);
    std::unordered_set<ll> greedySet = pipage_rounding(f_obj, x, I);
    return greedySet;
}