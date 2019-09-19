import java.util.*;

class DSU // DSU stands for Disjoint-set union
{
    int[] parent; // parent of each node
    int[] size; // number of nodes, in each nodes subtree
    public DSU(int n)
    {
        parent = new int[n + 1]; // arrays are 1-based
        size = new int[n + 1]; // size of subtree
        for(int i = 1; i <= n; i++)
        {
            parent[i] = i; // initially, each node is its own parent
            size[i] = 1; //  each tree has only one node
        }
    }
    int find(int u)
    {
        if(parent[u] == u) // am I in the root of tree?
            return u;
        return parent[u] = find(parent[u]); // also using path compression
            
    }
    void merge(int u, int v)
    {
        int pu = find(u); // pu = parent of u
        int pv = find(v); // pv = parent of v
        if(size[pu] > size[pv]) // if pu has a larger tree than pu
        {
            parent[pv] = pu; // pu becomes the parent of pv
            size[pu] += size[pv]; // adding all nodes in pv tree, to pu's subtree
        }
        else
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
    }
}

class Edge implements Comparable
{
    int head;
    int tail;
    int weight;
    
    public Edge(int _head, int _tail, int _weight)
    {
        head = _head;
        tail = _tail;
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
    static ArrayList <Edge> edgeList; // storing all the edges
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(), m = in.nextInt(); // number of vertices and edges respectively
        edgeList = new ArrayList<>();
        for(int i = 0; i < m; i++) // adding all edges with their weights to edgeList
        {
            int u = in.nextInt(), v = in.nextInt(), w = in.nextInt();
            Edge e = new Edge(u, v, w);
            edgeList.add(e);
        }
        Collections.sort(edgeList); // sort the edges using "compareTo" as comparator
        DSU disjoint = new DSU(n); // initializing a DSU
        int taken = 0; // number of edges in the MST
        int weightOfTree = 0; // weight of MST
        for(int i = 0; i < edgeList.size() && taken < n - 1; i++)
        {
            Edge e = edgeList.get(i); // lightest unseen edge
            if(disjoint.find(e.head) == disjoint.find(e.tail)) // connection will make a loop, tree doesn't have loop
                continue;
            taken++; // this edge is also in the MST
            weightOfTree += e.weight;
            disjoint.merge(e.head, e.tail); // make the connection
        }
        System.out.println(weightOfTree);
    }
}