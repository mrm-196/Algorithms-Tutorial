import java.util.*;

public class Main
{
    public static int[] a;
    public static int[] dp;
    public static int[] par;
    
    public static void init(int n)
    {
        a = new int[n];
        dp = new int[n];
        par = new int[n];
    }
    
    public static int LIS(int n)
    {
        dp[0] = 1;
        par[0] = -1;
        int maxi = 1;
        int maxIdx = 0;
        for (int i = 1; i < n; i++)
        {
            dp[i] = 1;
            par[i] = -1;
            for (int j = 0; j < i; j++)
            {
                if(a[i] > a[j] && dp[j] + 1 > dp[i])
                {
                    par[i] = j;
                    dp[i] = dp[j] + 1;
                    if(dp[i] > maxi)
                    {
                        maxi = dp[i];
                        maxIdx = i;
                    }
                }
            }
        }
        return maxIdx;
    }
    
    public static void printLIS(int idx)
    {
    	if(par[idx] == -1)
    	{
            System.out.print(a[idx] + " ");
    		return;
    	}
        printLIS(par[idx]);
        System.out.print(a[idx] + " ");
    }
    
    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        init(n);
        for(int i = 0; i < n; i++)
            a[i] = in.nextInt();
        int idx = LIS(n);
        System.out.println(dp[idx]);
        printLIS(idx);
        System.out.println("");
    }
}