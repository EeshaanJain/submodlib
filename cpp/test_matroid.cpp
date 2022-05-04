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
    std::uniform_int_distribution<int> unif(1, num_concepts / 2);
	uint64_t time_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::seed_seq ss{uint32_t(time_seed & 0xffffffff), uint32_t(time_seed >> 32)};
    rng.seed(ss);

    std::vector<int> all_concepts;
    for (int i = 0; i < num_concepts; i++)
    {
        all_concepts.push_back(i);
    }
    ll n = 7;
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
            std::cout << it << " ";
        }
        std::cout << "\n";
        coverset.push_back(curr);
    }

    std::vector<float> weights(num_concepts, 0.1);
    std::vector<ll> groundset(n);
    for (ll i = 0; i < n; i++)
    {
        groundset.push_back(i);
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
    SetCover* setcover = new SetCover(n, coverset, num_concepts, weights);
    std::unordered_set<ll> greedySet = setcover->maximize("AcceleratedContinuousGreedy", I);

    for (auto it: greedySet)
    {
        std::cout << it << " ";
    }
    std::cout << "\n";
}

// #include <iostream>
// #include <random>
// #include <string>
// #include <iterator>
// #include <experimental/algorithm>
 
// int main()
// {
//     std::vector<int> in = {1,2,3,4,5,6,7,8}, out;
//     std::experimental::sample(in.begin(), in.end(), std::back_inserter(out),
//                               5, std::mt19937{std::random_device{}()});
//     for (auto it: out)
//     {
//         std::cout << it << " ";
//     }
//     std::cout << "\n";
//     std::cout << "five random letters out of " << in[0] << " : " << out[1] << '\n';
// }