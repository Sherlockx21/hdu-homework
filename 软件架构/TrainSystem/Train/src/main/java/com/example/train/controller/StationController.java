package com.example.train.controller;

import com.example.train.pojo.*;
import com.example.train.service.*;
import com.example.train.util.ResponseResult;
import com.example.train.util.ToStationBoard;
import com.example.train.vo.StationBoard;
import com.example.train.vo.StationMap;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;


import javax.annotation.Resource;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.logging.Logger;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:46
 */
@RestController
@RequestMapping("/admin/stationcontroller")
public class StationController {
    private static final Logger LOG = Logger.getLogger(StationController.class.getName());

    @Resource
    private StationService stationService;
    @Resource
    private DistanceService distanceService;
    @Resource
    private SeatpriceService seatpriceService;
    @Resource
    private TrainsitService trainsitService;
    @Resource
    private TrainService trainService;

    private ToStationBoard toStationBoard;


    //展示车站列表
    @PostMapping("/StationList")
    public ResponseResult getStationList(){
        try {
            List<Station> stations = stationService.getAllStations();
            if(stations == null){
                return new ResponseResult<>("get Stationlist failed");
            }else{
                return new ResponseResult<>(stations);
            }
        }catch (Exception e){
            LOG.info("getStationListError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getStationListError");
    }

    //展示车站信息
    @RequestMapping("/getStation")
    public ResponseResult getStation(String station_name){
        try {
            Station station = stationService.getStationbyStationname(station_name);
            if(station == null){
                return new ResponseResult<>("no such station");
            }else {
                return new ResponseResult<>(station);
            }
        }catch(Exception e){
            LOG.info("getStationError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getStationError");
    }

    //展示车站详细信息，包括地点，过往火车及时间
    @RequestMapping("/showStationInfo")
    public ResponseResult showStationInfo(String station_name){
        try {
            Station station = stationService.getStationbyStationname(station_name);
            if(station == null){
                return new ResponseResult<>("no such station");
            }else {
                List<Trainsit> trainsits = trainsitService.getTrainsitbyStation(station_name);
                StationBoard stationBoard = toStationBoard.ParsetoStationBoard(trainsits);
                stationBoard.setStation_name(station_name);
                stationBoard.setCity_name(station.getCity_name());
                return new ResponseResult<>(station);
            }
        }catch(Exception e){
            LOG.info("getStationInfoError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getStationInfoError");
    }

    //添加车站基本信息
    @RequestMapping("/addStation")
    public ResponseResult addStation(String station_name,String city_name){
        try {
            Station station = stationService.getStationbyStationname(station_name);
            if(station == null){
                station.setStation_name(station_name);
                station.setCity_name(city_name);
                stationService.addStation(station);
                return new ResponseResult<>("add Station Success");
            }else{
                return new ResponseResult<>("Station already exist");
            }
        }catch (Exception e){
            LOG.info("addStationError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("addStationError");
    }

    //更新车站基本信息
    @RequestMapping("/updateStation")
    public ResponseResult updateStation(String station_name,String city_name){
        try {
            Station station = stationService.getStationbyStationname(station_name);
            if(station != null){
                station.setCity_name(city_name);
                stationService.updateStation(station);
                return new ResponseResult<>("update Station Success");
            }else{
                return new ResponseResult<>("Station doesn't exist");
            }
        }catch (Exception e){
            LOG.info("updateStationError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("updateStationError");
    }
    //删除车站
    @RequestMapping("/deleteStation")
    public ResponseResult deleteStation(String station_name){
        try {
            Station station = stationService.getStationbyStationname(station_name);
            if(station != null){
                stationService.deleteStation(station_name);//删除车站
                //删除包含车站的距离信息
                distanceService.deleteStation(station_name);
                //删除包含车站的票价信息
                seatpriceService.deleteStation(station_name);
                //删除包含此站的路径
                trainsitService.deleteStation(station_name);
                //更新火车信息
                List<String> train_numbers = trainService.getAllTrainnumber();
                for(String train_number:train_numbers){
                    trainService.refresh(train_number);
                }
                return new ResponseResult<>("delete Station Success");
            }else{
                return new ResponseResult<>("Station already deleted");
            }
        }catch (Exception e){
            LOG.info("deleteStationError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("deleteStationError");
    }
    @RequestMapping("/Distancelist")
    public ResponseResult listDistance(){
        try {
            List<Distance> distances = distanceService.getallDistance();
            if(distances == null){
                return new ResponseResult<>("getDistancelistFailed");
            }else {
                return new ResponseResult<>(distances);
            }
        }catch (Exception e){
            LOG.info("getDistancelistError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getDistancelistError");
    }
    @RequestMapping("/setDistance")
    public ResponseResult setDistance(String station_name1,String station_name2,int newdistance){
        try {
            //寻找距离信息
            Distance distance = distanceService.getDistancebyStationnames(station_name1,station_name2);
            if(distance != null){//找到，判断是否要更新
                if(distance.getDistance() != newdistance) {
                    distance.setDistance(newdistance);
                    distanceService.updateDistance(distance);
                }
                return new ResponseResult<>("update Distance Success");
            } else{//没找到，添加进距离列表
                distance.setStation_name1(station_name1);
                distance.setStation_name2(station_name2);
                distance.setDistance(newdistance);
                distanceService.addDistance(distance);
                return new ResponseResult<>("add Distance Success");
            }
        }catch (Exception e){
            LOG.info("setDistanceError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("setDistanceError");
    }
    @RequestMapping("/deleteDistance")
    public ResponseResult deleteDistance(Distance distance){
        try {
            Distance distance1 = distanceService.getDistancebyStationnames(distance.getStation_name1(), distance.getStation_name2());
            if(distance1 != null){//找到信息
                List<Station> stations = stationService.getAllStations();
                int stationnum = stations.size();
                //站点哈希映射
                Map<String,Integer> stationhash = new HashMap<>();
                for(int i=0;i < stationnum;i++){
                    stationhash.put(stations.get(i).getStation_name(),i);
                }
                //构建图
                StationMap stationMap = new StationMap(stationnum);
                List<Distance> distances2 = distanceService.getallDistance();
                for(Distance distance2:distances2){
                    stationMap.addtrails(stationhash.get(distance2.getStation_name1()),stationhash.get(distance2.getStation_name2()));
                }
                //去除边
                stationMap.removetrails(stationhash.get(distance.getStation_name1()),stationhash.get(distance.getStation_name2()));
                if(!stationMap.reachable(stationhash.get(distance1.getStation_name1()),stationhash.get(distance1.getStation_name2()))){
                    return new ResponseResult<>("Unable to delete an important trace");//删除后路径不可达的话，就报错
                }
                distanceService.deleteDistance(distance1);
                return new ResponseResult<>("delete Distance Success");
            }else{
                return new ResponseResult<>("Distance deleted already");
            }
        }catch (Exception e){
            LOG.info("deleteDistanceError:"+e);
            e.printStackTrace();
        }
        return new ResponseResult<>("deleteDistanceError");
    }
}
