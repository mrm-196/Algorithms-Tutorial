//LIS O(N^2)

#include <iostream>

using namespace std;

int a[1000], dp[1000], par[1000];
int n;

int LIS()
{
	dp[0] = 1;
	par[0] = -1;
	int maxi = 1;
	int maxIdx = 0;
	for (int i = 1; i < n; i++)
	{
		dp[i] = 1;
		par[i] = -1;
		for (int j = 0; j < i; j++)
		{
			if(a[i] > a[j] && dp[j] + 1 > dp[i])
			{
				par[i] = j;
				dp[i] = dp[j] + 1;
				if(dp[i] > maxi)
				{
					maxi = dp[i];
					maxIdx = i;
				}
			}
		}
	}
	return maxIdx;
}

void printLIS(int idx)
{
	if(par[idx] == -1)
	{
		cout << a[idx] << " ";
		return;
	}
	printLIS(par[idx]);
	cout << a[idx] << " ";
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int idx = LIS();
	cout << dp[idx] << endl; // length of LIS
	printLIS(idx); // print LIS
	cout << endl;
}