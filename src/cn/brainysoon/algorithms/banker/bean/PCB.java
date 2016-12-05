package cn.brainysoon.algorithms.banker.bean;

/**
 * Created by brainy on 16-12-5.
 */
public class PCB {

    /**
     * 对系统的依赖
     */
    private OS os;

    /**
     * 进程数量
     */
    private int numProcess;

    /**
     * 最大需求矩阵
     */
    private int[][] maxRequest;

    /**
     * 分配矩阵
     */
    private int[][] allocation;

    /**
     * 需求矩阵
     */
    private int[][] need;

    public PCB(OS os) {

        this.os = os;
    }

    public int getNumProcess() {
        return numProcess;
    }

    public int[][] getMaxRequest() {
        return maxRequest;
    }

    public int[][] getAllocation() {
        return allocation;
    }

    public int[][] getNeed() {
        return need;
    }

    public void setNumProcess(int numProcess) {
        this.numProcess = numProcess;
        this.maxRequest = new int[numProcess][os.getNumAvailavle()];
        this.allocation = new int[numProcess][os.getNumAvailavle()];
        this.need = new int[numProcess][os.getNumAvailavle()];
    }

    public void setMaxRequest(int i, int j, int value) {

        this.maxRequest[i][j] = value;
    }

    public void setAllocation(int i, int j, int value) {

        this.allocation[i][j] = value;
    }

    public void setNeed(int i, int j, int value) {

        this.need[i][j] = value;
    }
}
