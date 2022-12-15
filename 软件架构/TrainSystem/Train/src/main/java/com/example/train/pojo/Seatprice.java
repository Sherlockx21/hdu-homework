package com.example.train.pojo;

import org.springframework.stereotype.Component;

import java.io.Serializable;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 20:55
 */

public class Seatprice{

    private String train_number;//所属火车
    private String station_name;//所属站点
    private int station_order;//站点顺序
    private int principal_seat;//特等座数量
    private int first_seat;//一等座数量
    private int second_seat;//二等座数量
    private int hard_sleeper;//硬卧数量
    private int soft_sleeper;//软卧数量
    private int no_seat;//无座数量
    private int principal_seat_price;//特等座价格
    private int first_seat_price;//一等座价格
    private int second_seat_price;//二等座价格
    private int hard_sleeper_price;//硬卧价格
    private int soft_sleeper_price;//软卧价格
    private int no_seat_price;//无座价格

    public Seatprice() {
    }

    public Seatprice(String train_number, String station_name, int station_order, int principal_seat, int first_seat, int second_seat, int hard_sleeper, int soft_sleeper, int no_seat, int principal_seat_price, int first_seat_price, int second_seat_price, int hard_sleeper_price, int soft_sleeper_price, int no_seat_price) {
        this.train_number = train_number;
        this.station_name = station_name;
        this.station_order = station_order;
        this.principal_seat = principal_seat;
        this.first_seat = first_seat;
        this.second_seat = second_seat;
        this.hard_sleeper = hard_sleeper;
        this.soft_sleeper = soft_sleeper;
        this.no_seat = no_seat;
        this.principal_seat_price = principal_seat_price;
        this.first_seat_price = first_seat_price;
        this.second_seat_price = second_seat_price;
        this.hard_sleeper_price = hard_sleeper_price;
        this.soft_sleeper_price = soft_sleeper_price;
        this.no_seat_price = no_seat_price;
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
    public int getPrincipal_seat() {
        return principal_seat;
    }

    public void setPrincipal_seat(int principal_seat) {
        this.principal_seat = principal_seat;
    }

    public int getFirst_seat() {
        return first_seat;
    }

    public void setFirst_seat(int first_seat) {
        this.first_seat = first_seat;
    }

    public int getSecond_seat() {
        return second_seat;
    }

    public void setSecond_seat(int second_seat) {
        this.second_seat = second_seat;
    }

    public int getHard_sleeper() {
        return hard_sleeper;
    }

    public void setHard_sleeper(int hard_sleeper) {
        this.hard_sleeper = hard_sleeper;
    }

    public int getSoft_sleeper() {
        return soft_sleeper;
    }

    public void setSoft_sleeper(int soft_sleeper) {
        this.soft_sleeper = soft_sleeper;
    }

    public int getNo_seat() {
        return no_seat;
    }

    public void setNo_seat(int no_seat) {
        this.no_seat = no_seat;
    }

    public int getPrincipal_seat_price() {
        return principal_seat_price;
    }

    public void setPrincipal_seat_price(int principal_seat_price) {
        this.principal_seat_price = principal_seat_price;
    }

    public int getFirst_seat_price() {
        return first_seat_price;
    }

    public void setFirst_seat_price(int first_seat_price) {
        this.first_seat_price = first_seat_price;
    }

    public int getSecond_seat_price() {
        return second_seat_price;
    }

    public void setSecond_seat_price(int second_seat_price) {
        this.second_seat_price = second_seat_price;
    }

    public int getHard_sleeper_price() {
        return hard_sleeper_price;
    }

    public void setHard_sleeper_price(int hard_sleeper_price) {
        this.hard_sleeper_price = hard_sleeper_price;
    }

    public int getSoft_sleeper_price() {
        return soft_sleeper_price;
    }

    public void setSoft_sleeper_price(int soft_sleeper_price) {
        this.soft_sleeper_price = soft_sleeper_price;
    }

    public int getNo_seat_price() {
        return no_seat_price;
    }

    public void setNo_seat_price(int no_seat_price) {
        this.no_seat_price = no_seat_price;
    }

}
