#include <bits/stdc++.h> // this header is for GNU C++ compiler

/*
THESE HEADERS ARE FOR VISUAL STUDIO
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
*/

typedef long long ll;

using namespace std;

const int INF32 = (int)1e9;
const int MAXN = 10000; // maximum number of vertices

vector<int> adj[MAXN];
bool visited[MAXN];
int dist[MAXN];
int parent[MAXN];

void init()
{
	memset(parent, -1, sizeof parent); // parent of every node is -1
	memset(visited, false, sizeof visited); // all nodes are unvisited
	for(int i = 0; i < MAXN; i++)
		dist[i] = INF32; // set all distances to infinity at first (it means there is no path)
}

void BFS(int src)
{
	init();
	dist[src] = 0; // the distance between src and src is 0
	visited[src] = true;
	queue <int> q;
	q.push(src);
	while(!q.empty()) // until there are remaining vertices --> this loop runs exactly N times, if the graph is connected
	{
		int u = q.front(); // the node u is being inspected
		q.pop(); // we don't need to visit u later
		for(int i = 0; i < adj[u].size(); i++) // for each child of u --> this loops runs out-degree(u) times
		{
			int v = adj[u][i]; // v is a child of u
			if(!visited[v]) // if v is unvisited yet
			{
				visited[v] = true; // v is visited, don't visit it later
				dist[v] = dist[u] + 1; // v is a child of u, so it is one level lower than u
				parent[v] = u; // u is parent of v, we use this to print the path
				q.push(v); // add v for inspection
			}
		}
	}
}

void printPath(int destination)
{
	if(parent[destination] == -1) // we reached the root
	{
		cout << "Our path is: ";
		cout << destination + 1 << " "; // printing must be 1-based
		return;
	}
	printPath(parent[destination]); // print path to parent
	cout << destination + 1 << " "; // printing must be 1-based
}

int main()
{
	int n, m; // n = number of vertices, m = number of edges
	cin >> n >> m;
	for(int i = 0; i < m; i++)
	{
		int u, v;
		cin >> u >> v;
		u--; // 0-based
		v--; // 0-based
		adj[u].push_back(v); // add v to u's adjacency list
		adj[v].push_back(u); // we assume that our graph is bi-directional
	}
	BFS(0); // run BFS with 1 as the root (0-based)
	cout << "Enter the vertex you want its shortest path from 1: ";
	int k;
	cin >> k;
	if(dist[--k] == INF32) // the distance is infinity, so there is no path from 1 to k
	{
		cout << "There is no path from 1 to your vertex." << endl;
		return 0;
	}
	cout << "The shortest path has length " << dist[k] << endl;
	printPath(k); //print the vertices on the shortest path
	cout << endl;
}