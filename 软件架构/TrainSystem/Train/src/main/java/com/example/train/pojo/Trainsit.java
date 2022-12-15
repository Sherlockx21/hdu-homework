package com.example.train.pojo;

import org.springframework.stereotype.Component;

import java.io.Serializable;
import java.sql.Time;
import java.sql.Timestamp;
import java.util.Date;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:03
 */
public class Trainsit {
    private String train_number;
    private String station_name;
    private int station_order;
    private Timestamp arrival_time;
    private Time stayed_time;

    public Trainsit() {
    }

    public Trainsit(String train_number, String station_name, int station_order, Timestamp arrival_time, Time stayed_time) {
        this.train_number = train_number;
        this.station_name = station_name;
        this.station_order = station_order;
        this.arrival_time = arrival_time;
        this.stayed_time = stayed_time;
    }

    public String getTrain_number() {
        return train_number;
    }

    public void setTrain_number(String train_number) {
        this.train_number = train_number;
    }

    public String getStation_name() {
        return station_name;
    }

    public void setStation_name(String station_name) {
        this.station_name = station_name;
    }

    public int getStation_order() {
        return station_order;
    }

    public void setStation_order(int station_order) {
        this.station_order = station_order;
    }

    public Timestamp getArrival_time() {
        return arrival_time;
    }

    public void setArrival_time(Timestamp arrival_time) {
        this.arrival_time = arrival_time;
    }

    public Time getStay_time() {
        return stayed_time;
    }

    public void setStayed_time(Time stayed_time) {
        this.stayed_time = stayed_time;
    }
}
