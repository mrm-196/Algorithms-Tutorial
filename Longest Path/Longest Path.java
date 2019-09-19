import java.util.*;

public class Main {

    final static int MAX = 30; // maximum number of vertices

    static int[][] adj; // adjacency matrix
    static int[] sol, best; // current solution , best solution
    static int bestLen; // best solution's length
    static int n; // number of vertices
    static int destination; // destination of longest path problem

    static boolean promising(int level)
    {
	for (int i = 0; i < level - 1; i++) // make sure you have not visited the last vertex before
	{
		if(sol[level - 1] == sol[i])
			return false;
	}
	if(level == 1) // if there is only one vertex in the path
		return true;
	if(adj[sol[level - 2]][sol[level - 1]] == 0) // are two last vertices connected?
		return false;
	return true;
    }

    static void longestDistance(int src, int level)
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

    public static void main(String[] args) 
    {
        Scanner in = new Scanner(System.in);
        int m; // number of edges
        n = in.nextInt();
	m = in.nextInt();
        adj = new int[n][n];
        sol = new int[n];
        best = new int[n];
        for(int i = 0; i < n; i++) // initialize an empty graph
        {
            for(int j = 0; j < n; j++)
                adj[i][j] = 0;
        }
	for (int i = 0; i < m; i++) // add each edge
	{
		int u = in.nextInt(), v = in.nextInt();
                --u;
                --v;
		adj[u][v] = 1; // adj is 0-based
		adj[v][u] = 1;
	}
	int s = in.nextInt(), t = in.nextInt(); // source and destination of longest path problem
	s--; // 0-based
	t--;
	destination = t;
	bestLen = 0;
	sol[0] = s; // s is the first vertex in the path
	longestDistance(s, 1); // calculate longest distance between s and t
	for (int i = 0; i < bestLen; i++)
		          System.out.print((best[i] + 1) + " "); // print path
	System.out.println("");
    }
}
