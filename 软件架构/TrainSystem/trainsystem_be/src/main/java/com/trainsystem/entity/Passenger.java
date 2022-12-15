package com.trainsystem.entity;

import java.io.Serializable;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 18:55
 */
public class Passenger implements Serializable {
    private static final long serialVersionUID = 1L;
    private int pid;// 乘客编号
    private String trueName;// 真实姓名
    private String idCard;// 身份证号
    private int role;// 乘客身份：0代表成人票，1代表学生票

    public int getPid() {
        return pid;
    }

    public void setPid(int pid) {
        this.pid = pid;
    }

    public String getTrueName() {
        return trueName;
    }

    public void setTrueName(String trueName) {
        this.trueName = trueName;
    }

    public String getIdCard() {
        return idCard;
    }

    public void setIdCard(String idCard) {
        this.idCard = idCard;
    }

    public int getRole() {
        return role;
    }

    public void setRole(int role) {
        this.role = role;
    }

}
