package com.example.train.service.Impl;

import com.example.train.mapper.DistanceMapper;
import com.example.train.mapper.StationMapper;
import com.example.train.pojo.Distance;
import com.example.train.pojo.Station;
import com.example.train.service.DistanceService;
import com.example.train.vo.StationMap;
import lombok.val;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:31
 */
@Service
public class DistanceServiceImpl implements DistanceService {
    @Resource private DistanceMapper distanceMapper;
    @Resource private StationMapper stationMapper;
    @Resource private Distance distance;
    private List<Distance> distances;
    @Override
    public List<Distance> getallDistance(){
        distances = distanceMapper.getAllDistance();
        return distances;
    }
    @Override
    public Distance getDistancebyStationnames(String station_name1,String station_name2){
        distance = distanceMapper.getDistancebyStationnames(station_name1, station_name2);
        return distance;
    }
    @Override
    public List<Distance> getDistancebyStationname(String station_name){
        distances = distanceMapper.getDistancebyStationname(station_name);
        return distances;
    }
    @Override
    public void addDistance(Distance distance){
        distanceMapper.addDistance(distance);
    }
    @Override
    public void updateDistance(Distance distance){
        distanceMapper.updateDistance(distance);
    }
    @Override
    public void deleteDistance(Distance distance){
        List<Station> stations = stationMapper.getAllStations();
        int stationnum = stations.size();
        //站点哈希映射
        Map<String,Integer> stationhash = new HashMap<>();
        for(int i=0;i < stationnum;i++){
            stationhash.put(stations.get(i).getStation_name(),i);
        }
        //构建图
        StationMap stationMap = new StationMap(stationnum);
        List<Distance> distances1 = distanceMapper.getAllDistance();
        for(Distance distance1:distances1){
            stationMap.addtrails(stationhash.get(distance1.getStation_name1()),stationhash.get(distance1.getStation_name2()));
        }
        //去除边
        stationMap.removetrails(stationhash.get(distance.getStation_name1()),stationhash.get(distance.getStation_name2()));

        distanceMapper.deleteDistance(distance);
    }
//    @Override
//    public boolean reachable(String station_name1,String station_name2){
//        Distance distance = distanceMapper.getDistancebyStationnames(station_name1,station_name2);
//        if(distance == null){
//            distance = distanceMapper.getDistancebyStationnames(station_name2,station_name1);
//            if(distance != null) return true;
//        }else{
//            return true;
//        }
//        return false;
//    }
    @Override
    public void deleteStation(String station_name){
        List<Distance> distances = distanceMapper.getDistancebyStationname(station_name);
        List<Distance> distances1 = new ArrayList<>();
        List<Distance> distances2 = new ArrayList<>();
        for(Distance distance:distances){
            if(distance.getStation_name1() == station_name) {
                distances1.add(distance);//station作为起始站
            }
            if(distance.getStation_name2() == station_name) {
                distances2.add(distance);//station作为到达站
            }
            distanceMapper.deleteDistance(distance);
        }
        for(Distance distance1:distances1){
            for(Distance distance2:distances2){
                distance.setStation_name1(distance2.getStation_name1());
                distance.setStation_name2(distance1.getStation_name2());
                distance.setDistance(distance1.getDistance() + distance2.getDistance());
                Distance tmp = distanceMapper.getDistancebyStationnames(distance2.getStation_name1(),distance1.getStation_name2());
                if(tmp == null){//没有此路径
                    distanceMapper.addDistance(distance);
                }else{
                    if(tmp.getDistance() > distance.getDistance()){//选最短路径
                        distanceMapper.addDistance(distance);
                    }
                }
            }
        }
    }
}
