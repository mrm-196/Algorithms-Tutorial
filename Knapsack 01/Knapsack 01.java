import java.util.*;

/*
	Question:
		X has gone to rob a store. He can't carry more than W kilograms.
		There are N items in the store, each items has a weight and a value. What is the maximum value he can obtain from this robbery?
		W <= 10000
		N  <= 100
*/

public class Main
{
    public static int[] weight;
    public static int[] value;
    public static int[][] dp;
    
    public static int solve(int rem, int idx) // rem = remaining && idx = index
    {
        if(rem < 0) // Impossible
		return Integer.MIN_VALUE;
	if(idx < 0) // every object is visited, nothing to obtain
		return 0;
	if(dp[rem][idx] != -1) // the answer is calculated before
		return dp[rem][idx];
	
        // Let's calculate the answer
        int a = solve(rem - weight[idx], idx - 1) + value[idx]; // a = the maximum value we can obtain if we take this item
	int b = solve(rem, idx - 1); // b = the maximum value we can obtain if we don't take this item
        dp[rem][idx] = Integer.max(a, b); // store the maximal answer in the array, it won't be recalculated
        return dp[rem][idx];
    }
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        // W = knapsack's capacity
	// n = number of items
        int W = in.nextInt();
        int n = in.nextInt();
        weight = new int[n + 1];
        value = new int[n + 1];
        dp = new int[W + 1][n + 1];
        for(int i = 0; i < n; i++)
        {
            weight[i] = in.nextInt(); // weight of i'th object
            value[i] = in.nextInt(); // value of i'th object
        }
        // nothing is calculated yet
        for(int i = 0; i <= W; i++)
        {
            for(int j = 0; j <= n; j++)
                dp[i][j] = -1;
        }
        System.out.println(solve(W, n - 1));
        // O(nW)
    }
}