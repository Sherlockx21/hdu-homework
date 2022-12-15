package com.example.train.vo;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.List;
import java.util.Map;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 10:17
 */
public class Route {
    private String train_number;
    private List<String> stations;
    private List<Timestamp> arrival_times;
    private List<Time> stayed_times;
    private List<Map<String,Integer>> tickets;

    public String getTrain_number() {
        return train_number;
    }

    public void setTrain_number(String train_number) {
        this.train_number = train_number;
    }

    public List<String> getStations() {
        return stations;
    }

    public void setStations(List<String> stations) {
        this.stations = stations;
    }

    public List<Timestamp> getArrival_times() {
        return arrival_times;
    }

    public void setArrival_times(List<Timestamp> arrival_times) {
        this.arrival_times = arrival_times;
    }

    public List<Time> getStayed_times() {
        return stayed_times;
    }

    public void setStayed_times(List<Time> stayed_times) {
        this.stayed_times = stayed_times;
    }


    public List<Map<String, Integer>> getTickets() {
        return tickets;
    }

    public void setTickets(List<Map<String, Integer>> tickets) {
        this.tickets = tickets;
    }
}
