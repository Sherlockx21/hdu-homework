package com.example.train.service.Impl;

import com.example.train.mapper.DistanceMapper;
import com.example.train.mapper.StationMapper;
import com.example.train.pojo.Distance;
import com.example.train.pojo.Station;
import com.example.train.service.StationService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:45
 */
@Service
public class StationServiceImpl implements StationService {
    @Resource
    private StationMapper stationMapper;
    @Resource
    private Station station;
    private List<Station> stations;
    @Override
    public List<Station> getAllStations(){
        stations = stationMapper.getAllStations();
        return stations;
    }
    @Override
    public Station getStationbyStationname(String station_name){
        station = stationMapper.getStationbyStationname(station_name);
        return station;
    }
    @Override
    public void addStation(Station station){
        stationMapper.addStation(station);
    }
    @Override
    public void updateStation(Station station){
        stationMapper.updateStation(station);
    }
    @Override
    public void deleteStation(String station_name){
        stationMapper.deleteStation(station_name);
    }

}
