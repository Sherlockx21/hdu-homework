package com.example.train.service.Impl;

import com.example.train.mapper.DistanceMapper;
import com.example.train.mapper.SeatpriceMapper;
import com.example.train.pojo.Distance;
import com.example.train.pojo.Seatprice;
import com.example.train.service.SeatpriceService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Comparator;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:12
 */
@Service
public class SeatpriceServiceImpl implements SeatpriceService {
    @Resource
    private SeatpriceMapper seatpriceMapper;
    @Resource
    private DistanceMapper distanceMapper;
    @Resource
    private Seatprice seatprice;
    private List<Seatprice> seatprices;

    @Override
    public List<Seatprice> getAllSeatprice(){
        seatprices = seatpriceMapper.getAllSeatprice();
        return seatprices;
    }
    @Override
    public Seatprice getSeatprice(String train_number,String station_name){
        seatprice = seatpriceMapper.getSeatprice(train_number,station_name);
        return seatprice;
    }
    @Override
    public List<Seatprice> getSeatpricebyTrain(String train_number){
        seatprices = seatpriceMapper.getSeatpricebyTrain(train_number);
        return seatprices;
    }
    @Override
    public List<Seatprice> getSeatpricebyStation(String station_name){
        seatprices = seatpriceMapper.getSeatpricebyStation(station_name);
        return seatprices;
    }
    @Override
    public void addSeatprice(Seatprice seatprice){
        seatpriceMapper.addSeatprice(seatprice);
    }
    @Override
    public void updateSeatprice(Seatprice seatprice){
        seatpriceMapper.updateSeatprice(seatprice);
    }
    @Override
    public void deleteSeatprice(String train_number,String station_name){
        seatpriceMapper.deleteSeatprice(train_number,station_name);
    }
    @Override
    public void deleteStation(String station_name){
        List<Seatprice> seatprices = seatpriceMapper.getSeatpricebyStation(station_name);//查找包含这站的票
        for(Seatprice seatprice:seatprices){
            int count = 1;//记录删掉了几站
            String train_number = seatprice.getTrain_number();
            int order = seatprice.getStation_order();
            //得到路径上的车票信息
            List<Seatprice> seatprices1 = seatpriceMapper.getSeatpricebyTrain(train_number);
            seatprices1.sort(Comparator.comparing(Seatprice::getStation_order));//按站点升序排序
//            Seatprice former = null;//记录前一站
//            for(Seatprice seatprice1:seatprices1){
//                if(seatprice1.getStation_order() < order) {//在此站之前，必可达
//                    former = seatprice1;//成为前一站
//                } else if(seatprice1.getStation_order() == order){
//                    continue;
//                }else{
//                    //后一站与前一站联通，火车可达
//                    if(reachable(former.getStation_name(), seatprice1.getStation_name()) || former == null){
//                        seatprice1.setStation_order(seatprice1.getStation_order() - count);
//                        seatpriceMapper.updateSeatprice(seatprice1);
//                        former = seatprice1;
//                    }else{//不可达，删除信息
//                        seatpriceMapper.deleteSeatprice(train_number,seatprice1.getStation_name());
//                        count++;
//                    }
//                }
            for(Seatprice seatprice1:seatprices1){
                if(seatprice1.getStation_order() <= order){
                    continue;//在此站之前，不做处理
                }else{
                    seatprice1.setStation_order(seatprice1.getStation_order()-1);
                    seatpriceMapper.updateSeatprice(seatprice1);
                }
            }
            seatpriceMapper.deleteSeatprice(train_number,station_name);
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
