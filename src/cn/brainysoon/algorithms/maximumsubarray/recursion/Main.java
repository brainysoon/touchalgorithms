package cn.brainysoon.algorithms.maximumsubarray.recursion;

import java.util.Scanner;

/*
 * 最大子数组的 递归实现 时间复杂度 O(nlogn)
 * 首先介绍一下 递归实现的伪代码  //杭电 1003
 *
 * FIND_CROSSING_SUBARRAY(A,low,mid,high)
 * left_sum=-&
 * sum=0
 * for i=mid downto low
 *      sum+=A[i]
 *      if sum>left_sum
 *          left_sum=sum
 *          max_left=i
 * right_sum=-&
 * sum=0
 * for j=mid+1 to high
 *      sum+=A[j]
 *      if sum>right_sum
 *          right_sum=sum
 *          max_right=j
 *  return (max_left,max_right,left_sum+right_sum)
 *
 *  FIND_MAXIMUM_SUBARRAY(A,low,high)
 *  if low==high
 *      return (low,high,A[low])
 *  else mid=[(low+hgit)/2]
 *      (left_low,left_high,left_sum)=FIND_MAXIMUM_SUBARRAY(A,low,mid)
 *      (right_low,right_high,right_sum)=FIND_MAXIMUM_SUBARRAY(A,mid+1,high)
 *      (cross_low,cross_high,cross_sum)=FIND_CROSSING_SUBARRAY(A,low,mid,high)
 *
 *      if left_sum>=right_sum&&left_sum>=cross_sum
 *          return (left_low,left_high,left_sum)
 *      else if right_sum>=left_sum&&right_sum>=cross_sum
 *          return (right_low,right_high,right_sum)
 *      else
 *          return (cross_low,cross_high,cross_sum)
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

            Bean resultBean = findMaxmumSubarray(A, 0, A.length - 1);

            System.out.println("Case " + i + ":");
            System.out.println(resultBean.sum + " " + (resultBean.left + 1) + " " + (resultBean.right + 1));
        }
    }

    public static Bean findMaxmumSubarray(int[] A, int low, int high) {

        //work 4.1-4
        if (A.length == 0) {

            return new Bean(0, 0, 0);
        }

        if (low == high) {

            return new Bean(low, high, A[low]);
        } else {

            int mid = (low + high) / 2;

            Bean leftBean = findMaxmumSubarray(A, low, mid);
            Bean rightBean = findMaxmumSubarray(A, mid + 1, high);
            Bean crossBean = findCrossingSubarray(A, low, mid, high);

            if (leftBean.sum >= rightBean.sum && leftBean.sum >= crossBean.sum) {

                return leftBean;
            } else if (rightBean.sum >= leftBean.sum && rightBean.sum >= crossBean.sum) {

                return rightBean;
            } else {

                return crossBean;
            }
        }
    }

    public static Bean findCrossingSubarray(int[] A, int low, int mid, int high) {

        Bean crossBean = new Bean();

        int left_sum = Integer.MIN_VALUE;
        int sum = 0;
        for (int i = mid; i >= 0; i--) {

            sum += A[i];
            if (sum > left_sum) {

                left_sum = sum;
                crossBean.left = i;
            }
        }

        int right_sum = Integer.MIN_VALUE;
        sum = 0;
        for (int j = mid + 1; j <= high; j++) {

            sum += A[j];
            if (sum > right_sum) {
                right_sum = sum;
                crossBean.right = j;
            }
        }

        crossBean.sum = left_sum + right_sum;

        return crossBean;
    }
}

class Bean {
    int left;
    int right;
    int sum;

    public Bean() {
        super();
    }

    public Bean(int left, int right, int sum) {

        this.left = left;
        this.right = right;
        this.sum = sum;
    }
}
