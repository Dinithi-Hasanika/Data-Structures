import java.util.TreeMap;
import java.util.TreeSet;

class Q4 {
    static int [][] cost = {{0, 3, 12, 23, 41}, // cost from 0
            {0, 0,  2,  4, 34}, // cost from 1
            {0, 0,  0,  12, 3}, // cost from 2
            {0, 0,  0,  0, 12}, // cost from 3
            {0, 0,  0,  0,  0}  // cost from 4
    };

    static int iMax = 5;
    static int jMax = 5;

    // Just for testing, min cost from 0 to 4 should be 8.
    static int answer = 8;

    static int[][]minCost_mem ={{-1,-1,-1,-1,-1}, {-1,-1,-1,-1,-1}, {-1,-1,-1,-1,-1} ,{-1,-1,-1,-1,-1} ,{-1,-1,-1,-1,-1}};

    public static int minCost(int i, int j) {
        // broken implementation
        if (i == j || i+1 == j) {
            return cost[i][j];
        }
        if(minCost_mem[i][j] != -1){
            return minCost_mem[i][j];
        }
        int minValue = cost[i][j];

        for (int k = i+1; k<j; k++)
        {
            int check = minCost(i, k) +
                    minCost( k, j);
            if (check < minValue) {
                minValue = check;
                minCost_mem[i][j] = minValue;
            }
        }
        return minValue;

    }

    public static void main(String [] args) {
        int r = minCost(0,4);
        if(r == answer)
            System.out.println("Your implementation might be correct");
        else
            System.out.println("Too bad. Try again (" + r + ")");
    }
}
