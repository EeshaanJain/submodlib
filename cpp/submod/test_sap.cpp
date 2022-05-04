#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>
#include <map>
#include <random>
#include <unordered_set>
#include "Sap.h"

using namespace std;

int main()
{
    vector<vector<double>> cost = {{1, 2}, {3, 4}, {2, 1}};
    vector<vector<unordered_set<ll>>> v = {{unordered_set<ll>({0}), unordered_set<ll>({1}), unordered_set<ll>({0, 1})},
                                           {unordered_set<ll>({1}), unordered_set<ll>({2}), unordered_set<ll>({1, 2})}};

    for (int i = 0; i < 1; i++)
    {
        Sap sap(cost, v);
        auto res = sap.maximize("ContinuousGreedy", false, false, cost);

        for (auto r : res)
        {
            for (auto rr : r)
            {
                cout << rr << " ";
            }
            cout << endl;
        }

        auto res2 = sap.evaluateFinalSet();
        for (auto r : res2)
        {
            for (auto rr : r)
            {
                cout << rr << " ";
            }
            cout << endl;
        }
    }
}