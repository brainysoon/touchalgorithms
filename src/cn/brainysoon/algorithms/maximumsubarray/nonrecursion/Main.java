package cn.brainysoon.algorithms.maximumsubarray.nonrecursion;

import java.util.Scanner;

/*
 * 最大子数组 非递归实现
 *
 *  FIND_MAXIMUM_SUBARRAY(A,low,high)
 *  max_sum=a[0]
 *  for i=1 to A.length
 *      sum=A[i]
 *      temp_sum=[i]
 *      for j=i-1 downto 0
 *          sum+=A[j]
 *          if sum>temp_sum
 *              temp_sum=sum
 *              left=j
 *      if temp_sum>max_sum
 *          max_sum=temp_sum
 *          max_left=left;
 *          max_right=i;
 */
public class Main {

    public static void main(String[] args) {

        Scanner cin = new Scanner(System.in);

        int T = cin.nextInt();

        for (int i = 1; i <= T; i++) {

            int n = cin.nextInt();

            int[] A = new int[n];

            for (int j = 0; j < n; j++) {

                A[j] = cin.nextInt();
            }

            Bean resultBean = findMaximumSubarray(A, 0, A.length - 1);
            System.out.println("Case " + i + ":");
            System.out.println(resultBean.sum + " " + (resultBean.left + 1) + " " + (resultBean.right + 1));
        }
    }

    public static Bean findMaximumSubarray(int[] A, int low, int high) {

        Bean bean = new Bean();

        bean.sum = A[0];
        bean.left = 0;
        bean.right = 0;

        for (int i = 1; i < A.length; i++) {

            int sum = A[i];
            int temp_sum = A[i];
            int left = i;

            for (int j = i - 1; j >= 0; j--) {

                sum += A[j];
                if (sum >= temp_sum) {

                    temp_sum = sum;
                    left = j;
                }
            }

            if (temp_sum > bean.sum) {

                bean.sum = temp_sum;
                bean.left = left;
                bean.right = i;
            }
        }

        return bean;
    }
}

class Bean {

    int left;
    int right;
    int sum;
}