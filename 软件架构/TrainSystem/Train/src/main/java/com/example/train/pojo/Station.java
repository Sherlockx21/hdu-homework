package com.example.train.pojo;


import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;

import java.io.Serializable;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 19:47
 */

public class Station{
    private String station_name;//站点名称
    private String city_name;//城市名称

    public Station() {
    }

    public Station(String station_name, String city_name) {
        this.station_name = station_name;
        this.city_name = city_name;
    }

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
}
