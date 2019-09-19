#include <bits/stdc++.h>

using namespace std;

// maximum input size
#define MAXN 100000

/*
	a --> input array
	tail --> tail-table (its length is equal with LIS)
	indexOnA[i] --> indexOf i'th element of tail-table on A
	parOnA[i] --> parent index (on input array)
*/
int a[MAXN], tail[MAXN], indexOnA[MAXN], parOnA[MAXN];


// print LIS elements recursively
void print(int lastIndex)
{
	if(parOnA[lastIndex] == -1) // if no parent is remaining
	{
		cout << a[lastIndex] << " ";
		return;
	}
	print(parOnA[lastIndex]); // print previous elements
	cout << a[lastIndex] << " "; // print current element
}

int main()
{
	int n; // input array length
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	int len = 0; // LIS length
	if(n == 0) // corner case, empty array
	{
		cout << n << endl;
		return 0;
	}
	memset(parOnA, -1, sizeof parOnA); // no element has parent
	tail[len++] = a[0]; // add a[0] to tail-table
	for (int i = 1; i < n; i++)
	{
		if(a[i] > tail[len - 1]) // is it possible to extend tail-table?
		{
			indexOnA[len] = i; // indexOnA is i
			parOnA[i] = indexOnA[len - 1]; // previous element on tail-table is placed at [len - 1], so its indexOnA is indexOnA[len - 1]
			tail[len++] = a[i]; // add current element as the last (largest) element
		}
		else if(a[i] == tail[len - 1]) // is this element useless (result is STRICTLY increasing)
			continue;
		else if(a[i] <= tail[0]) // can this element become the smallest element of tail-table?
		{
			indexOnA[0] = i;
			tail[0] = a[i];
		}
		else
		{
			int index = lower_bound(tail, tail + len, a[i]) - tail; // binarySearch for the appropriate index
			indexOnA[index] = i;
			parOnA[i] = indexOnA[index - 1]; // previous element becomes the parent
			tail[index] = a[i]; // current element will replace the smallest number, which is larger than current element
		}
	}
	cout << "Length = " << len << endl; // len is equal to LIS length
	cout << "LIS = ";
	print(indexOnA[len - 1]); // print(k) --> k = Last element of LIS's indexOnA
	cout << endl;
}