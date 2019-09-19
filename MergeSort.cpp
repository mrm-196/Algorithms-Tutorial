#include <bits/stdc++.h>

using namespace std;

int a[20000];
int temp[20000];

int doMerge(int low, int high)
{
	int mid = (low + high) / 2;
	int i = 0, j = mid + 1, k = 0;
	while(i <= mid && j <= high)
	{
		if(a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}
	while(i <= mid)
		temp[k++] = a[i++];
	while(j <= high)
		temp[k++] = a[j++];
	for (int x = low; x <= high; x++)
		a[x] = temp[x];
}

void MSort(int low, int high)
{
	if(low == high)
		return;
	int mid = (low + high) / 2;
	MSort(low, mid);
	MSort(mid + 1, high);
	doMerge(low, high);
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	MSort(0, n - 1);
	for (int i = 0; i < n; i++)
		cout << a[i] << " ";
}