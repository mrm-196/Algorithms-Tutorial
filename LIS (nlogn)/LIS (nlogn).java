import java.util.*;

public class Main
{
    /*
        a --> input array
        tail --> tail-table (its length is equal with LIS)
        indexOnA[i] --> indexOf i'th element of tail-table on A
        parOnA[i] --> parent index (on input array)
    */
    static int[] a, tail, indexOnA, parOnA;

    public static void main(String[] args)
    {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(); // input array's length

        // initializing arrays
        a = new int[n];
        tail = new int[n];
        indexOnA = new int[n];
        parOnA = new int[n];
        for (int i = 0; i < n; i++)
        {
            a[i] = in.nextInt();
            parOnA[i] = -1; // no element has parent
        }

        int len = 0; // LIS length
        if(n == 0) // corner case, empty array
        {
            System.out.println(n);
            return;
        }
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
                int x = Arrays.binarySearch(tail,0, len, a[i]); // binarySearch for the appropriate index
                int index = -x - 1; // for more information: https://www.tutorialspoint.com/java/util/arrays_binarysearch_int_index.htm
                indexOnA[index] = i;
                parOnA[i] = indexOnA[index - 1]; // previous element becomes the parent
                tail[index] = a[i]; // current element will replace the smallest number, which is larger than current element
            }
        }
        System.out.println("Length = " + len); // len is equal to LIS length
        System.out.print("LIS = ");
        print(indexOnA[len - 1]);  // print(k) --> k = Last element of LIS's indexOnA
        System.out.println();
    }


    // print LIS elements recursively
    static void print(int lastIndex)
    {
        if(parOnA[lastIndex] == -1) // if no parent is remaining
        {
            System.out.print(a[lastIndex] + " ");
            return;
        }
        print(parOnA[lastIndex]); // print previous elements
        System.out.print(a[lastIndex] + " " ); // print current element
    }
}
