package com.trainsystem.entity;

import java.io.Serializable;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 18:24
 */
public class Train implements Serializable {
    private static final long serialVersionUID = 1L;
    private String tid;// 车次编号
    //private String ttype;// 车辆类型
    private String stype1;// 座位类型1
    private int scount1;// 座位余票1
    private double tmoney1;// 票价1
    private String stype2;// 座位类型2
    private int scount2;// 座位余票2
    private double tmoney2;// 票价2
    private String stype3;// 座位类型3
    private int scount3;// 座位余票3
    private double tmoney3;// 票价3
    private String stype4;// 座位类型4
    private int scount4;// 座位余票4
    private double tmoney4;// 票价4
    private String stype5;// 座位类型5
    private int scount5;// 座位余票5
    private double tmoney5;// 票价5
    private String stype6;// 座位类型6
    private int scount6;// 座位余票6
    private double tmoney6;// 票价6
    private double runtime;// 车程耗时：单位是小时
    private int salesum;// 售出总票数
    private int stacount;// 途径站次
    private List<Station> stationList;// 车站列表

    public String getTid() {
        return tid;
    }

    public void setTid(String tid) {
        this.tid = tid;
    }

//    public String getTtype() {
//        return ttype;
//    }
//
//    public void setTtype(String ttype) {
//        this.ttype = ttype;
//    }

    public String getStype1() {
        return stype1;
    }

    public void setStype1(String stype1) {
        this.stype1 = stype1;
    }

    public int getScount1() {
        return scount1;
    }

    public void setScount1(int scount1) {
        this.scount1 = scount1;
    }

    public double getTmoney1() {
        return tmoney1;
    }

    public void setTmoney1(double tmoney1) {
        this.tmoney1 = tmoney1;
    }

    public String getStype2() {
        return stype2;
    }

    public void setStype2(String stype2) {
        this.stype2 = stype2;
    }

    public int getScount2() {
        return scount2;
    }

    public void setScount2(int scount2) {
        this.scount2 = scount2;
    }

    public double getTmoney2() {
        return tmoney2;
    }

    public void setTmoney2(double tmoney2) {
        this.tmoney2 = tmoney2;
    }

    public String getStype3() {
        return stype3;
    }

    public void setStype3(String stype3) {
        this.stype3 = stype3;
    }

    public int getScount3() {
        return scount3;
    }

    public void setScount3(int scount3) {
        this.scount3 = scount3;
    }

    public double getTmoney3() {
        return tmoney3;
    }

    public void setTmoney3(double tmoney3) {
        this.tmoney3 = tmoney3;
    }

    public String getStype4() { return stype4; }

    public void setStype4(String stype4){ this.stype4 = stype4; }

    public int getScount4() {return scount4;}

    public void setScount4(int scount4) {
        this.scount4 = scount4;
    }

    public double getTmoney4() {
        return tmoney4;
    }

    public void setTmoney4(double tmoney4) {
        this.tmoney4 = tmoney4;
    }

    public String getStype5() {
        return stype5;
    }

    public void setStype5(String stype5) {
        this.stype5 = stype5;
    }

    public int getScount5() {
        return scount5;
    }

    public void setScount5(int scount5) {
        this.scount5 = scount5;
    }

    public double getTmoney5() {
        return tmoney5;
    }

    public void setTmoney5(double tmoney5) {
        this.tmoney5 = tmoney5;
    }
    public String getStype6() {
        return stype6;
    }

    public void setStype6(String stype6) {
        this.stype6 = stype6;
    }

    public int getScount6() {
        return scount6;
    }

    public void setScount6(int scount6) {
        this.scount6 = scount6;
    }

    public double getTmoney6() {
        return tmoney6;
    }

    public void setTmoney6(double tmoney6) {
        this.tmoney6 = tmoney6;
    }

    public double getRuntime() {
        return runtime;
    }

    public void setRuntime(double runtime) {
        this.runtime = runtime;
    }

    public int getSalesum() {
        return salesum;
    }

    public void setSalesum(int salesum) {
        this.salesum = salesum;
    }

    public List<Station> getStationList() {
        return stationList;
    }

    public void setStationList(List<Station> stationList) {
        this.stationList = stationList;
    }

    public int getStacount() {
        return stacount;
    }

    public void setStacount(int stacount) {
        this.stacount = stacount;
    }

}

