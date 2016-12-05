package cn.brainysoon.algorithms.banker;

import cn.brainysoon.algorithms.banker.algorithms.BankerAlgorithm;
import cn.brainysoon.algorithms.banker.algorithms.SafeAlgorithm;
import cn.brainysoon.algorithms.banker.bean.OS;
import cn.brainysoon.algorithms.banker.bean.PCB;

import java.util.Scanner;

/**
 * Created by brainy on 16-12-5.
 */
public class Main {
    /* 书上一组测试数据
1
3
10 5 7
5
7 5 3
1
0 1 0
3 2 2
1
2 0 0
9 0 2
1
3 0 2
2 2 2
1
2 1 1
4 3 3
1
0 0 2

     */

    private static OS os;
    private static PCB pcb;
    private static SafeAlgorithm safeAlgorithm;
    private static BankerAlgorithm bankerAlgorithm;
    private static Scanner cin;

    public static void main(String[] args) {

        cin = new Scanner(System.in);

        while (true) {

            try {

                showMenu();
                int n = cin.nextInt();

                switch (n) {

                    case 1:
                        initData();
                        break;

                    case 2:
                        request();
                        break;

                    case 3:
                        showOS();
                        break;

                    case 4:
                        showPCB();
                        break;

                    case 5:
                        return;

                    default:
                        System.out.println("输入的指令有误！");
                        break;
                }

            } catch (Exception e) {

                System.out.println("内部错误！");
                e.printStackTrace();
            }
        }
    }

    /**
     * 显示菜单
     */
    public static void showMenu() {

        System.out.println("****** Java版 银行家算法模拟系统 ******");
        System.out.println("*      1. 初始化模拟数据              ");
        System.out.println("*      2. 申请系统资源                ");
        System.out.println("*      3. 显示系统资源信息            ");
        System.out.println("*      4. 显示进程资源信息            ");
        System.out.println("*      5. 退出                       ");
        System.out.println("*************************************");
    }

    /**
     * 初始化数据
     */
    public static void initData() {

        System.out.println("****** 请输入系统资源的总数目 ******");
        int n = cin.nextInt();

        os = new OS();
        os.setNumAvailavle(n);

        System.out.println("****** 请输入可利用资源的最大数目 ******");
        for (int i = 0; i < n; i++) {

            System.out.print("资源" + (i + 1) + "的最大值：");

            int max = cin.nextInt();

            os.getAvailable()[i] = max;
        }

        System.out.println("****** 请输入进程的总数目 ******");
        int m = cin.nextInt();

        pcb = new PCB(os);

        pcb.setNumProcess(m);

        System.out.println("****** 请输入相应进程的最大需求 ******");
        for (int i = 0; i < m; i++) {

            System.out.println("****** 进程" + (i + 1) + "需求 ******");

            for (int j = 0; j < n; j++) {

                System.out.print("请输入进程 " + (i + 1) + "对资源 " + (j + 1) + "的最大需求:");


                int maxRequest = cin.nextInt();
                pcb.getMaxRequest()[i][j] = maxRequest;
            }

            System.out.println("是否需要设置 该进程已分配的资源？(1 需要/ 0 不需要");
            int flag = cin.nextInt();

            if (flag > 0) {

                for (int j = 0; j < n; j++) {

                    System.out.print("请输入进程 " + (i + 1) + "对资源 " + (j + 1) + "的已分配数量:");

                    int temp = cin.nextInt();
                    pcb.getAllocation()[i][j] = temp;
                    pcb.getNeed()[i][j] = pcb.getMaxRequest()[i][j] - temp;
                    os.getAvailable()[j] -= temp;
                }
            } else {

                for (int j = 0; j < n; j++) {

                    pcb.getNeed()[i][j] = pcb.getMaxRequest()[i][j];
                }
            }
        }

    }

    /**
     * 申请系统资源
     */
    public static void request() {

        if (os == null || pcb == null) {

            System.out.println("请先初始化数据！");
            return;
        }

        System.out.println("****** 请输入需要申请资源的进程号 ******");
        int p = cin.nextInt();

        p--;

        int[] request = new int[os.getNumAvailavle()];

        System.out.println("****** 请输入相应资源的数目 ******");
        for (int i = 0; i < os.getNumAvailavle(); i++) {

            System.out.print("输入资源 " + (i + 1) + "的资源数目:");
            int requestValue = cin.nextInt();

            request[i] = requestValue;
        }

        //申请资源
        if (safeAlgorithm == null || bankerAlgorithm == null) {

            safeAlgorithm = new SafeAlgorithm(os, pcb);
            bankerAlgorithm = new BankerAlgorithm(os, pcb, safeAlgorithm);
        }
        System.out.println("****** 申请结果 ******");
        System.out.println(bankerAlgorithm.performBankerAlgorithm(p, request));

        /*
        System.out.println("****** 是否需要打印 安全性检查表？(1 需要/0 不需要)");
        int temp = cin.nextInt();

        if (temp > 0) {

            System.out.println("    资源情况    |     Need     |    Allocation   | Work+Allocation |    Finish    ");
            System.out.print("资源编号：");

            for (int i = 0; i < os.getNumAvailavle(); i++) {
                System.out.print("  " + (i + 1));
            }
            System.out.print("|");
            for (int i = 0; i < os.getNumAvailavle(); i++) {
                System.out.print("  " + (i + 1));
            }
            System.out.print("|");
            for (int i = 0; i < os.getNumAvailavle(); i++) {
                System.out.print("  " + (i + 1));
            }
            System.out.print("|");
            for (int i = 0; i < os.getNumAvailavle(); i++) {
                System.out.print("  " + (i + 1));
            }
            System.out.print("|");

            System.out.println();

            for (int i = 0; i < pcb.getNumProcess(); i++) {

                System.out.print("进程 " + (i + 1)+": ");

                for (int j = 0; j < os.getNumAvailavle(); j++) {

                    System.out.print("  "+safeAlgorithm.getWork()[i]);
                }
            }

        }
        */
    }

    /**
     *
     */
    public static void showOS() {

        if (os == null) {

            System.out.println("请先初始化数据！");
            return;
        }

        System.out.println("****** 系统资源信息 ******");

        System.out.print("资源编号：");
        for (int i = 0; i < os.getNumAvailavle(); i++) {

            System.out.print("    " + (i + 1));
        }
        System.out.println();

        System.out.print("可以用：");
        for (int i = 0; i < os.getNumAvailavle(); i++) {

            System.out.print("    " + (os.getAvailable()[i]));
        }
        System.out.println();
    }

    /**
     * 显示进程信息
     */
    public static void showPCB() {

        if (os == null || pcb == null) {

            System.out.println("请先初始化数据!");
            return;
        }

        System.out.println("****** 显示进程信息 ******");
        for (int i = 0; i < pcb.getNumProcess(); i++) {

            System.out.println(">>>进程 " + (i + 1) + "信息：");

            System.out.print("资源编号：");
            for (int j = 0; j < os.getNumAvailavle(); j++) {

                System.out.print("    " + (j + 1));
            }
            System.out.println();

            System.out.print("最大需求：");
            for (int j = 0; j < os.getNumAvailavle(); j++) {

                System.out.print("    " + pcb.getMaxRequest()[i][j]);
            }
            System.out.println();

            System.out.print("已分配  :");
            for (int j = 0; j < os.getNumAvailavle(); j++) {

                System.out.print("    " + pcb.getAllocation()[i][j]);
            }
            System.out.println();

            System.out.print("需求    :");
            for (int j = 0; j < os.getNumAvailavle(); j++) {

                System.out.print("    " + pcb.getNeed()[i][j]);
            }
            System.out.println();
        }
    }
}
