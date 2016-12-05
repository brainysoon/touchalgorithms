package cn.brainysoon.algorithms.banker.algorithms;

import cn.brainysoon.algorithms.banker.bean.OS;
import cn.brainysoon.algorithms.banker.bean.PCB;

/**
 * Created by brainy on 16-12-5.
 */
public class SafeAlgorithm {

    /**
     * 系统依赖
     */
    private OS os;

    /**
     * 进程依赖
     */
    private PCB pcb;

    /**
     * 工作向量
     */
    private int[] work;

    /**
     * 记录是否有足够的资源分配给进程
     */
    private boolean[] finish;

    /**
     * 记录安全序列
     */
    private int[] safe;
    private boolean[] markSafe;
    private boolean isSafe;

    public SafeAlgorithm(OS os, PCB pcb) {

        this.os = os;
        this.pcb = pcb;

        //初始化工作向量
        this.work = new int[os.getNumAvailavle()];
        for (int i = 0; i < os.getNumAvailavle(); i++) {

            this.work[i] = os.getAvailable()[i];
        }

        //初始化记录向量
        this.finish = new boolean[pcb.getNumProcess()];
        for (int i = 0; i < pcb.getNumProcess(); i++) {

            this.finish[i] = false;
        }

        //初始化安全序列
        this.safe = new int[pcb.getNumProcess()];
        this.isSafe = false;
        this.markSafe = new boolean[pcb.getNumProcess()];
    }

    public boolean performSafeAlgorithm() {

        for (int i = 0; i < pcb.getNumProcess(); i++) {
            markSafe[i] = false;
        }

        findSafeSequence(0);

        return this.isSafe;
    }

    public void findSafeSequence(int index) {

        if (index < pcb.getNumProcess()) {

            for (int i = 0; i < pcb.getNumProcess(); i++) {

                if (!markSafe[i]) {

                    safe[index] = i;
                    markSafe[i] = true;
                    findSafeSequence(index + 1);
                    markSafe[i] = false;
                }
            }
        } else {

            //出口
            //安全性检查算法

            //首先
            initActors();

            for (int k = 0; k < pcb.getNumProcess(); k++) {

                int i = safe[k];

                boolean flag = true;

                if (!finish[i]) {

                    for (int j = 0; j < os.getNumAvailavle(); j++) {

                        if (pcb.getNeed()[i][j] > work[j]) {

                            flag = false;
                            break;
                        }
                    }

                    if (flag) {

                        for (int j = 0; j < os.getNumAvailavle(); j++) {

                            work[j] += pcb.getAllocation()[i][j];
                        }

                        finish[i] = true;
                    }
                }
            }

            for (int i = 0; i < pcb.getNumProcess(); i++) {

                if (!finish[i]) {

                    return;
                }
            }
            this.isSafe = true;

            System.out.print("找到一个安全序列 >>>>>>");
            for (int i = 0; i < pcb.getNumProcess(); i++) {

                System.out.print(" " + (safe[i] + 1));
            }
            System.out.println();
        }
    }

    public void initActors() {

        //清零工作向量
        for (int i = 0; i < os.getNumAvailavle(); i++) {

            this.work[i] = os.getAvailable()[i];
        }

        //清零记录向量
        for (int i = 0; i < pcb.getNumProcess(); i++) {

            this.finish[i] = false;
        }
    }

    public int[] getWork() {
        return work;
    }

    public boolean[] getFinish() {
        return finish;
    }
}