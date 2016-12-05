package cn.brainysoon.algorithms.matrixmultiplication.violence;

/**
 * Created by brainy on 16-12-1.
 */
public class Main {

    public static void main(String[] args) {


    }

    public static int[][] matrixMultiplication(int[][] A, int[][] B) {

        int n = A.length;

        int[][] C = new int[n][n];

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < n; j++) {

                int c = 0;

                for (int k = 0; k < n; k++) {

                    c += A[j][k] * B[k][i];
                }

                C[i][j] = c;
            }
        }

        return C;
    }
}
