#include <bits/stdc++.h>

/*
	Question:
		X has gone to rob a store. He can't carry more than W kilograms.
		There are N items in the store, each items has a weight and a value. What is the maximum value he can obtain from this robbery?
		W <= 10000
		N  <= 100
*/

const int INF32 = (int)1e9;

using namespace std;

int weight[105], value[105];
int dp[10005][105];

int solve(int rem, int idx) // rem = remaining && idx = index
{
	if(rem < 0) // Impossible
		return -INF32;
	if(idx < 0) // every object is visited, nothing to obtain
		return 0;
	if(dp[rem][idx] != -1) // the answer is calculated before
		return dp[rem][idx];
	
	// Let's calculate the answer
	int a = solve(rem - weight[idx], idx - 1) + value[idx]; // a = the maximum value we can obtain if we take this item
	int b = solve(rem, idx - 1); // b = the maximum value we can obtain if we don't take this item
	dp[rem][idx] = max(a, b); // store the maximal answer in the array, it won't be recalculated
	return dp[rem][idx];
}

int main()
{
	// W = knapsack's capacity
	// n = number of items
	int W, n;
	cin >> W >> n;
	for(int i = 0; i < n; i++)
		cin >> weight[i] >> value[i]; // weight of i'th object && value of i'th object
	memset(dp, -1, sizeof dp); // nothing is calculated yet
	cout << solve(W, n - 1) << endl;
	// O(nW)
}