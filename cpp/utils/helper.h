#include <unordered_set>
#include <functional>
#include <numeric>
#include <vector>
#include <random>

typedef long long int ll;
float dot_prod(std::vector<float> &v1, std::vector<float> &v2);
float mag(std::vector<float> &v);
float cosine_similarity(std::vector<float> &v1, std::vector<float> &v2);
float euclidean_distance(std::vector<float> &v1, std::vector<float> &v2);
float euclidean_similarity(std::vector<float> &v1, std::vector<float> &v2);

struct datapoint_pair
{
	ll i1;
	ll i2;
	float val;
	datapoint_pair(ll a = 0, ll b = 0, float c = 0);
};

bool operator<(datapoint_pair lval, datapoint_pair rval);

std::vector<std::vector<float>> create_kernel(std::vector<std::vector<float>> &X, std::string metric, ll num_neigh);
std::vector<std::vector<float>> create_kernel_NS(std::vector<std::vector<float>> &X_ground, std::vector<std::vector<float>> &X_master, std::string metric);
std::vector<std::vector<float>> create_square_kernel_dense(std::vector<std::vector<float>> &X_ground, std::string metric);
std::unordered_set<ll> set_intersection(std::unordered_set<ll> const &a, std::unordered_set<ll> const &b);
std::unordered_set<ll> set_union(std::unordered_set<ll> const &a, std::unordered_set<ll> const &b);

// Ipsit, Sibasis, Eeshaan
struct hash_function_set
{
	std::size_t operator()(const std::unordered_set<ll> &s) const
	{
		ll sum = 0;
		std::hash<ll> hasher;
		for (auto it = s.begin(); it != s.end(); it++)
		{
			sum += hasher(*it);
		}
		return sum;
	}
};

struct pair_hash
{
	inline std::size_t operator()(const std::pair<ll, ll> &v) const
	{
		return v.first * 31 + v.second;
	}
};

ll matroid_rank(std::unordered_set<std::unordered_set<ll>, hash_function_set> &I);
ll matroid_rank(std::unordered_set<ll> &S, std::unordered_set<std::unordered_set<ll>, hash_function_set> &I);
ll get_index(std::unordered_set<ll> &s, ll k);
std::unordered_set<ll> R(std::vector<double> &x, std::unordered_set<ll> &S, std::unordered_set<ll> &groundSet, double eps, std::mt19937_64 rng, std::uniform_real_distribution<double> unif);