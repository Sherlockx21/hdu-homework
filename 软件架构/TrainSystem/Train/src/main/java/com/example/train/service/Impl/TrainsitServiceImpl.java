package com.example.train.service.Impl;

import com.example.train.mapper.DistanceMapper;
import com.example.train.mapper.TrainsitMapper;
import com.example.train.pojo.Distance;
import com.example.train.pojo.Trainsit;
import com.example.train.service.TrainsitService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Comparator;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:24
 */
@Service
public class TrainsitServiceImpl implements TrainsitService {
    @Resource
    private TrainsitMapper trainsitMapper;
    @Resource
    private DistanceMapper distanceMapper;
    @Resource
    private Trainsit trainsit;
    private List<Trainsit> trainsits;
    @Override
    public List<Trainsit> getAllTrainsits(){
        trainsits = trainsitMapper.getAllTrainsits();
        return trainsits;
    }
    @Override
    public Trainsit getTrainsit(String train_number,String station_name){
        trainsit = trainsitMapper.getTrainsit(train_number,station_name);
        return trainsit;
    }
    @Override
    public List<Trainsit> getTrainsitbyTrain(String train_number){
        trainsits = trainsitMapper.getTrainsitbyTrain(train_number);
        return trainsits;
    }
    @Override
    public List<Trainsit> getTrainsitbyStation(String station_name){
        trainsits = trainsitMapper.getTrainsitbyStation(station_name);
        return trainsits;
    }
    @Override
    public void addTrainsit(Trainsit trainsit){
        trainsitMapper.addTrainsit(trainsit);
    }
    @Override
    public void updateTrainsit(Trainsit trainsit){
        trainsitMapper.updateTrainsit(trainsit);
    }
    @Override
    public void deleteTrainsit(String train_number,String station_name){
        trainsitMapper.deleteTrainsit(train_number,station_name);
    }
    @Override
    public void deleteStation(String station_name){
        List<Trainsit> trainsits = trainsitMapper.getTrainsitbyStation(station_name);
        for(Trainsit trainsit:trainsits){
            //int count = 1;//记录删掉了几站
            String train_number = trainsit.getTrain_number();
            int order = trainsit.getStation_order();
            //得到路径上的车票信息
            List<Trainsit> trainsits1 = trainsitMapper.getTrainsitbyTrain(train_number);
            trainsits1.sort(Comparator.comparing(Trainsit::getStation_order));//按站点升序排序
//            Trainsit former = null;//记录前一站
//            for(Trainsit trainsit1:trainsits1){
//                if(trainsit1.getStation_order() < order) {//在此站之前，必可达
//                    former = trainsit1;//成为前一站
//                } else if(trainsit1.getStation_order() == order){
//                    continue;
//                }else{
//                    if(reachable(former.getStation_name(), trainsit1.getStation_name()) || former == null){
//                        trainsit1.setStation_order(trainsit1.getStation_order() - 1);
//                        trainsitMapper.updateTrainsit(trainsit1);
//                        former = trainsit1;
//                    }else{//不可达，删除信息
//                        trainsitMapper.deleteTrainsit(train_number,trainsit1.getStation_name());
//                        count++;
//                    }
//                }
//
//            }
            for(Trainsit trainsit1:trainsits1){
                if(trainsit1.getStation_order() <= order){
                    continue;
                }else{
                    trainsit1.setStation_order(trainsit1.getStation_order()-1);
                    trainsitMapper.updateTrainsit(trainsit);
                }
            }
            trainsitMapper.deleteTrainsit(train_number,station_name);
        }
    }
//    private boolean reachable(String station_name1,String station_name2){
//        Distance distance = distanceMapper.getDistancebyStationnames(station_name1,station_name2);
//        if(distance == null){
//            distance = distanceMapper.getDistancebyStationnames(station_name2,station_name1);
//            if(distance != null) return true;
//        }else{
//            return true;
//        }
//        return false;
//    }
}
