package com.example.train.pojo;

import org.springframework.stereotype.Component;

import java.io.Serializable;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:25
 */
public class Distance{
    private String station_name1;//站点一
    private String station_name2;//站点二
    private int distance;//距离

    public Distance() {
    }

    public Distance(String station_name1, String station_name2, int distance) {
        this.station_name1 = station_name1;
        this.station_name2 = station_name2;
        this.distance = distance;
    }

    public String getStation_name1() {
        return station_name1;
    }

    public void setStation_name1(String station_name1) {
        this.station_name1 = station_name1;
    }

    public String getStation_name2() {
        return station_name2;
    }

    public void setStation_name2(String station_name2) {
        this.station_name2 = station_name2;
    }

    public int getDistance() {
        return distance;
    }

    public void setDistance(int distance) {
        this.distance = distance;
    }
}
