package com.example.train.service;

import com.example.train.pojo.Station;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:45
 */

public interface StationService {
    public List<Station> getAllStations();
    public Station getStationbyStationname(String station_name);
    public void addStation(Station station);
    public void updateStation(Station station);
    public void deleteStation(String station_name);
}
