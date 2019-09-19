#include <bits/stdc++.h>

using namespace std;

#define MAX 30 // maximum number of vertices

int adj[MAX][MAX]; // adjacency matrix
int sol[MAX], best[MAX]; // current solution , best solution
int bestLen; // best solution's length
int n; // number of vertices
int destination; // destination of longest path problem

bool promising(int level)
{
	for (int i = 0; i < level - 1; i++) // make sure you have not visited the last vertex before
	{
		if(sol[level - 1] == sol[i])
			return false;
	}
	if(level == 1) // if there is only one vertex in the path
		return true;
	if(!adj[sol[level - 2]][sol[level - 1]]) // are two last vertices connected?
		return false;
	return true;
}

void longestDistance(int src, int level)
{
	if(!promising(level)) // is the current answer reliable?
		return;
	if(src == destination) // have I reached the destination?
	{
		if(level > bestLen) // is my answer better than the answer which is currently the best?
		{
			for (int i = 0; i < level; i++)
				best[i] = sol[i]; // update best path
			bestLen = level; // update length of best path
		}
		return;
	}
	for (int i = 0; i < n; i++)
	{
		sol[level] = i; // this may continue my answer
		longestDistance(i, level + 1); // let's see what we get with vertex i
	}
}

int main()
{
	int m; // number of edges
	memset(adj, 0, sizeof adj); // empty graph
	cin >> n >> m;
	for (int i = 0; i < m; i++) // add each edge
	{
		int u, v;
		cin >> u >> v;
		adj[--u][--v] = 1; // adj is 0-based
		adj[v][u] = 1;
	}
	int s, t; // source and destination of longest path problem
	cin >> s >> t;
	s--; // 0-based
	t--;
	destination = t;
	bestLen = 0;
	sol[0] = s; // s is the first vertex in the path
	longestDistance(s, 1); // calculate longest distance between s and t
	for (int i = 0; i < bestLen; i++)
		cout << best[i] + 1 << " "; // print path
	cout << endl;
}