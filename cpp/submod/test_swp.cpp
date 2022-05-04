#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <set>
#include <iterator>
#include <map>
#include <random>
#include "Swp.h"

using namespace std;

int main()
{
    vector<vector<double>> costs = {{0, 1, 2, 3, 3, 5, 4, 6}, {0, 2, 2, 3, 1, 3, 2, 4}};
    int groundSetSize = 3;

    for (int i = 0; i < 10; i++)
    {
        Swp swp(costs, groundSetSize);
        auto res = swp.maximize("ContinuousGreedy", false, false, costs);

        for (auto r : res)
        {
            for (auto rr : r)
            {
                cout << rr << " ";
            }
            cout << endl;
        }

        auto res2 = swp.evaluateFinalSet();
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