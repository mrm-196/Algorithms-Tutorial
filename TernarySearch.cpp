#include <bits/stdc++.h>

using namespace std;

int a[20000];

int TernarySearch(int low, int high)
{
	if(high - low <= 3)
		return *max_element(a + low, a + high + 1);
	int mid1 = (2 * low + high) / 3;
	int mid2 = (2 * high + low) / 3;
	if(a[mid1] > a[mid2])
		return TernarySearch(low, mid2);
	else
		return TernarySearch(mid1, high);
}

int main()
{
	int n;
	cin >> n;
	// array A taa ye jaayi increasing hastesh, az unja be bad decreasing mishe --> A yedune gholle daare
	// un gholle ro peida konid
	for (int i = 0; i < n; i++)
		cin >> a[i];
	cout << TernarySearch(0, n - 1) << endl;
}