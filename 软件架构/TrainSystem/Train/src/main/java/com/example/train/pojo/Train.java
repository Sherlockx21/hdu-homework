package com.example.train.pojo;

import org.springframework.stereotype.Component;

import java.io.Serializable;
import java.sql.Timestamp;
import java.util.Date;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 19:38
 */
public class Train {
    private String train_number;// 车次编号
    private String start_station;//起始站
    private String  end_station;//终点站
    private Timestamp start_time;//出发时间
    private Timestamp end_time;//结束时间

    public Train() {
    }

    public Train(String train_number, String start_station, String end_station, Timestamp start_time, Timestamp end_time) {
        this.train_number = train_number;
        this.start_station = start_station;
        this.end_station = end_station;
        this.start_time = start_time;
        this.end_time = end_time;
    }

    public void setTrain_number(String train_number){
        this.train_number = train_number;
    }

    public String getTrain_number(){
        return this.train_number;
    }

    public String getStart_station() {
        return start_station;
    }

    public void setStart_station(String start_station) {
        this.start_station = start_station;
    }

    public String getEnd_station() {
        return end_station;
    }

    public void setEnd_station(String end_station) {
        this.end_station = end_station;
    }

    public Date getStart_time() {
        return start_time;
    }

    public void setStart_time(Timestamp start_time) {
        this.start_time = start_time;
    }

    public Date getEnd_time() {
        return end_time;
    }

    public void setEnd_time(Timestamp end_time) {
        this.end_time = end_time;
    }
}
