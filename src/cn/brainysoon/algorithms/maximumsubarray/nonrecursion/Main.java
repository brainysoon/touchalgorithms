package cn.brainysoon.algorithms.maximumsubarray.nonrecursion;

/*
 *  最大子数组 非递归实现 //动态规划
 *
 *  FIND_MAXIMUM_SUBARRAY(A,low,high)
 *  sub_sum=-&
 *  cross_sum=-&
 *  for i=0 to A.length
 *      if cross_sum<0
 *          cross_sum=0
 *          cross_left=i
 *      cross_sum+=A[i]
 *      cross_right=i
 *      if cross_sum>sub_sum
 *          sub_sum=cross_sum
 *          sub_left=cross_left
 *          sub_right=cross_right
 */

import java.util.Scanner;

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
            if (i < T) System.out.println();
        }
    }

    public static Bean findMaximumSubarray(int[] A, int low, int high) {

        Bean bean = new Bean();
        Bean cross = new Bean();

        bean.sum = Integer.MIN_VALUE;
        cross.sum = Integer.MIN_VALUE;

        for (int i = low; i <= high; i++) {

            if (cross.sum < 0) {

                cross.sum = 0;
                cross.left = i;
            }

            cross.sum += A[i];
            cross.right = i;

            if (cross.sum > bean.sum) {

                bean.sum = cross.sum;
                bean.left = cross.left;
                bean.right = cross.right;
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