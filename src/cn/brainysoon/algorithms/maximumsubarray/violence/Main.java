package cn.brainysoon.algorithms.maximumsubarray.violence;

import java.util.Scanner;

/*
 * 最大子数组 暴力破解 时间复杂度 O(n2)
 *
 *  FIND_MAXIMUM_SUBARRAY(A,low,high)
 *  max_sum=-&
 *  for i=0 to A.length
 *      sum=A[i]
 *      for j=i+1 to A.length
 *          sum+=A[j]
 *          if sum>max_sum
 *              max_sum=sum
 *              left=i
 *              right=j
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

        bean.sum = Integer.MIN_VALUE;

        for (int i = low; i <= high; i++) {

            int sum = A[i];

            for (int j = i + 1; j <= high; j++) {

                sum += A[j];
                if (sum > bean.sum) {
                    bean.sum = sum;
                    bean.left = i;
                    bean.right = j;
                }

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