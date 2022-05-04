#include <iostream>
#include <unordered_set>
#include <random>
#include <chrono>
// #include <algorithm>
#include <iterator>
#include <vector>
#include <experimental/algorithm>
#include"submod/SetCover.h"
// #include"utils/helper.h"
typedef long long int ll;


int main()
{       
    int num_concepts = 10;
    std::mt19937_64 rng;
    std::uniform_int_distribution<int> unif(1, num_concepts);
	uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32)};
    rng.seed(ss);

    std::vector<int> all_concepts;
    for (int i = 0; i < num_concepts; i++)
    {
        all_concepts.push_back(i);
    }
    ll n = 9;
    std::vector<std::unordered_set<int>> coverset;
    for (ll i = 0; i < n; i++)
    {
        int j = unif(rng);
        std::vector<int> out;
        std::experimental::sample(all_concepts.begin(), all_concepts.end(), std::back_inserter(out), j, std::mt19937{std::random_device{}()});
        std::unordered_set<int> curr;
        for (auto it: out)
        {
            curr.insert(it);
            // std::cout << it << " ";
        }
        // std::cout << "\n";
        coverset.push_back(curr);
    }

    std::vector<float> weights(num_concepts, 0.1);
    std::vector<ll> groundset(n);
    for (ll i = 0; i < n; i++)
    {
        groundset[i] = i;
    }
    std::unordered_set<std::unordered_set<ll>, hash_function_set> I;
    for (ll i = 0; i < (1 << n); i++)
    {
        std::unordered_set<ll> sub;
        for (ll j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                sub.insert(groundset[j]);
            }
        }
        I.insert(sub);
    }
    SetCover setcover(n, coverset, num_concepts, weights);
    std::unordered_set<ll> greedySet = setcover.maximize("AcceleratedContinuousGreedy", I);

    for (auto it: greedySet)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
}