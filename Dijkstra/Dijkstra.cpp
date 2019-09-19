#include <bits/stdc++.h>

const int INF32 = (int)1e9;

using namespace std;

#define MAXN 20005

struct Edge
{
	int weight; // where is this edge heading?
	int toward; // how heavy is this edge?
};

bool operator<(const Edge &e1, const Edge &e2)
{
	return (e2.weight < e1.weight);
}

int dist[MAXN]; // distance from source
int parent[MAXN];
vector <Edge> adj[MAXN]; // adjacency list
// Dijkstra doesn't need "visited" array

void init()
{
	for(int i = 0; i < MAXN; i++)
	{
		dist[i] = INF32;
		parent[i] = -1;
	}
}

int shortestPath(int source, int destination)
{
	init(); // nobody has parent. all nodes are distant.
	dist[source] = 0; // source has distance 0 with itself
	priority_queue <Edge> pq; // initialize a Heap
	Edge ee;
	ee.weight = 0;
	ee.toward = source;
	pq.push(ee); // adding source, with 0 as distance, to the Heap
	while(!pq.empty())
	{
		ee = pq.top(); // extracting the nearest vertex to source
		pq.pop();
		int u = ee.toward; // who is the extracted vertex?
		int w = ee.weight; // how long is the distance between source and u?
		for(int i = 0; i < adj[u].size(); i++) // for all vertices connected to u
		{
			Edge v = adj[u][i]; // i'th edge connected to u
			if(dist[v.toward] > w + v.weight) // Have I found a better answer?
			{
				dist[v.toward] = v.weight + w; // update the answer
				parent[v.toward] = u; // update the ancestor
				ee.weight = dist[v.toward];
				ee.toward = v.toward;
				pq.push(ee); // add the updated vertex to the heap with its new distance, so its children will be updated too.
			}
		}
	}
	return dist[destination]; // the distance between source and destination
}

void printPath(int source, int destination)
{
	if(source == destination) // Am I at the beginning?
	{
		cout << "The shortest path: " << source << " ";
		return;
	}
	printPath(source, parent[destination]); // print the path to my parent
	cout << destination << " "; // add me to the end of my parent's path
}

int main()
{
	int n, m, s, t; // n -> number of vertices ### m -> number of edges ### s -> source ### t -> destination
	cin >> n >> m >> s >> t;
	for(int i = 0; i < m; i++) // add each edge
	{
		int u, v, w; // u -> head of edge ### v -> tail of edge ### w -> weight of edge
		cin >> u >> v >> w;
		Edge e;
		e.weight = w;
		e.toward = v;
		adj[u].push_back(e);
		e.toward = u;
		adj[v].push_back(e); // our graph is bidirectional
	}
	int d = shortestPath(s, t); // distance between s and t
	if(d < INF32) // distance is not infinite
	{
		cout << d << endl;
		printPath(s, t);
		cout << endl;
	}
	else
		cout << "unreachable" << endl;
}