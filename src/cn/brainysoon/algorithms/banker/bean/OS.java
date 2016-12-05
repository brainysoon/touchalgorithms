package cn.brainysoon.algorithms.banker.bean;

/**
 * Created by brainy on 16-12-5.
 */
public class OS {

    /**
     * 可用资源的数目
     */
    private int numAvailavle;

    /**
     * 全部可用资源的数目
     */
    private int[] available;

    public int getNumAvailavle() {
        return numAvailavle;
    }

    public int[] getAvailable() {
        return available;
    }

    public void setNumAvailavle(int numAvailavle) {
        this.numAvailavle = numAvailavle;
        this.available = new int[numAvailavle];
    }

    public void setAvailable(int i, int value) {

        this.available[i] = value;
    }
}
