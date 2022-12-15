package com.example.train.service;

import com.example.train.pojo.Distance;
import com.example.train.pojo.Station;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:31
 */
public interface DistanceService {
    public List<Distance> getallDistance();
    public Distance getDistancebyStationnames(String station_name1,String station_name2);
    public List<Distance> getDistancebyStationname(String station_name);
    public void addDistance(Distance distance);
    public void updateDistance(Distance distance);
    public void deleteDistance(Distance distance);
    //public boolean reachable(String station_name1,String station_name2);
    public void deleteStation(String station_name);
}
