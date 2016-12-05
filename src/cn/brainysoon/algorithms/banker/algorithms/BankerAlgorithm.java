package cn.brainysoon.algorithms.banker.algorithms;

import cn.brainysoon.algorithms.banker.bean.OS;
import cn.brainysoon.algorithms.banker.bean.PCB;

/**
 * Created by brainy on 16-12-5.
 */
public class BankerAlgorithm {

    /**
     * 系统依赖
     */
    private OS os;

    /**
     * 进程依赖
     */
    private PCB pcb;

    /**
     * 安全性算法
     */
    private SafeAlgorithm safeAlgorithm;

    public BankerAlgorithm(OS os, PCB PCB, SafeAlgorithm safeAlgorithm) {

        this.os = os;
        this.pcb = PCB;
        this.safeAlgorithm = safeAlgorithm;
    }

    public String performBankerAlgorithm(int p, int[] request) {

        //检查是否请求资源是否小于需求
        for (int i = 0; i < request.length; i++) {

            if (request[i] > pcb.getNeed()[p][i]) {

                return "所需要的资源数已经超过所需要的最大值！";
            }
        }

        //检查是否有足够的资源
        for (int i = 0; i < request.length; i++) {

            if (request[i] > os.getAvailable()[i]) {

                return "尚无足够的资源，需等待！";
            }
        }

        //尝试修改数据
        for (int i = 0; i < request.length; i++) {

            os.getAvailable()[i] -= request[i];
            pcb.getAllocation()[p][i] += request[i];
            pcb.getNeed()[p][i] -= request[i];
        }

        //安全性检查
        if (safeAlgorithm.performSafeAlgorithm()) {

            return "资源申请成功！";
        } else {

            //恢复数据
            for (int i = 0; i < request.length; i++) {

                os.getAvailable()[i] += request[i];
                pcb.getAllocation()[p][i] -= request[i];
                pcb.getNeed()[p][i] += request[i];
            }

            return "无法通过安全性检查，申请资源失败！";
        }
    }
}