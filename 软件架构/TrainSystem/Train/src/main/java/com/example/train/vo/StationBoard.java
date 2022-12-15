package com.example.train.vo;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 14:37
 */
public class StationBoard {
    private String station_name;
    private String city_name;
    private List<String> train_numbers;
    private List<Timestamp> arrivaltimes;
    private List<Time> stayed_times;

    public String getStation_name() {
        return station_name;
    }

    public void setStation_name(String station_name) {
        this.station_name = station_name;
    }

    public String getCity_name() {
        return city_name;
    }

    public void setCity_name(String city_name) {
        this.city_name = city_name;
    }

    public List<String> getTrain_numbers() {
        return train_numbers;
    }

    public void setTrain_numbers(List<String> train_numbers) {
        this.train_numbers = train_numbers;
    }

    public List<Timestamp> getArrivaltimes() {
        return arrivaltimes;
    }

    public void setArrivaltimes(List<Timestamp> arrivaltimes) {
        this.arrivaltimes = arrivaltimes;
    }

    public List<Time> getStayed_times() {
        return stayed_times;
    }

    public void setStayed_times(List<Time> stayed_times) {
        this.stayed_times = stayed_times;
    }

}
