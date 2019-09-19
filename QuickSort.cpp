#include <bits/stdc++.h>

using namespace std;

#define MAXN 2005

int a[MAXN];

int partition(int low, int high)
{
	int pivot = a[low];
	int l = low + 1;
	int r = high;
	while (true)
	{
		while (a[l] <= pivot && r >= l)
			l++;
		while (a[r] >= pivot && r >= l)
			r--;
		if (l >= r)
		{
			swap(a[r], a[low]);
			return r;
		}
		swap(a[l], a[r]);
	}
}

void quickSort(int low, int high)
{
	if(low >= high)
		return;
	if(low + 1 == high)
	{
		if(a[low] > a[high])
			swap(a[low], a[high]);
		return;
	}
	int pivot = partition(low, high); 	// pivot index
	quickSort(low, pivot - 1);			// do quickSort for the left half
	quickSort(pivot + 1, high);			// do quickSort for the right half
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
	cout << endl;
}