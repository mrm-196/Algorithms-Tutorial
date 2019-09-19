import java.util.*;

class Edge implements Comparable
{
    int toward; // where is this edge heading?
    int weight; // how heavy is this edge?
    
    public Edge(int _toward, int _weight)
    {
        toward = _toward;
        weight = _weight;
    }
    
    /*
        How java undestands compareTo:
            if returned number is equal to 0, it means that two objects are equal
            if returned number is less than zero, it means that current object is less than function's argument
            if returned number is more than zero, it means that current object is more than function's argument
    */
    @Override
    public int compareTo(Object e)
    {
        return weight - ((Edge)e).weight;
    }
}

public class Main
{
    final static int MAXN = 20005;
    
    static ArrayList[] adj; // adjacency list
    static int[] parent;
    static int[] dist; // distance from source
    // Dijkstra doesn't need "visited" array
    
    static void init()
    {
        adj = new ArrayList[MAXN];
        parent = new int[MAXN];
        dist = new int[MAXN];
        for(int i = 0; i < MAXN; i++)
        {
            parent[i] = -1; // nobody has parent
            adj[i] = new ArrayList();
            dist[i] = Integer.MAX_VALUE; // all nodes are distant
        }
    }
    
    static int shortestPath(int source, int distance)
    {
        dist[source] = 0; // source has distance 0 with itself
        Edge ee = new Edge (source, 0);
        PriorityQueue pq = new PriorityQueue(); // initialize a Heap
        pq.add(ee); // adding source, with 0 as distance, to the Heap
        while(!pq.isEmpty())
        {
            ee = (Edge)pq.poll(); // extracting the nearest vertex to source
            int u = ee.toward; // who is the extracted vertex?
            int w = ee.weight; // how long is the distance between source and u?
            for(int i = 0; i < adj[u].size(); i++) // for all vertices connected to u
            {
                Edge v = (Edge)adj[u].get(i); // i'th edge connected to u
                if(dist[v.toward] > w + v.weight) // Have I found a better answer?
                {
                    dist[v.toward] = w + v.weight; // update the answer
                    parent[v.toward] = u; // update the ancestor
                    Edge Jadid = new Edge(v.toward, dist[v.toward]);
                    pq.add(Jadid); // add the updated vertex to the heap with its new distance, so its children will be updated too.
                }
            }
        }
        return dist[distance]; // the distance between source and destination
    }
    
    static void printPath(int source, int destination)
    {
        if(source == destination) // Am I at the beginning?
        {
            System.out.print(source + " ");
            return;
        }
        printPath(source, parent[destination]); // print the path to my parent
        System.out.print(destination + " "); // add me to the end of my parent's path
    }
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        // n -> number of vertices ### m -> number of edges ### s -> source ### t -> destination
        int n = in.nextInt(), m = in.nextInt(), s = in.nextInt(), t = in.nextInt();
        init();
        for(int i = 0; i < m; i++) // add each edge
        {
            // u -> head of edge ### v -> tail of edge ### w -> weight of edge
            int u = in.nextInt(), v = in.nextInt(), w = in.nextInt();
            Edge e = new Edge(v, w);
            Edge er = new Edge(u, w);
            adj[u].add(e);
            adj[v].add(er); // our graph is bidirectional
        }
        int d = shortestPath(s, t); // distance between s and t
        if(parent[t] == -1 && s != t) // distance is infinite
            System.out.println("unreachable");
        else
        {
            System.out.println(d);
            printPath(s, t);
            System.out.println("");
        }
    }
}