package com.example.train.controller;

import com.example.train.pojo.Seatprice;
import com.example.train.pojo.Station;
import com.example.train.pojo.Train;
import com.example.train.pojo.Trainsit;
import com.example.train.service.*;
import com.example.train.util.ResponseResult;
import com.example.train.util.ToRoute;
import com.example.train.vo.Route;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;


import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.logging.Logger;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:45
 */
@RestController
@RequestMapping("/admin/traincontroller")
public class TrainController {
    private static final Logger LOG = Logger.getLogger(TrainController.class.getName());

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

    private ToRoute toRoute;

    @CrossOrigin

    //展示所有火车
    @RequestMapping(value = "/gettrainlist",method = RequestMethod.POST)
    public ResponseResult getTrainList(){
        try {
            List<Train> trains = trainService.getAllTrains();
            if(trains == null){
                return new ResponseResult<>("get Trainlist failed");
            }else{
                return new ResponseResult<>(trains);
            }
        }catch (Exception e){
            LOG.info("getTrainListError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getTrainListError");
    }

    //找到一辆火车
    @PostMapping(value = "/Train")
    @ResponseBody
    public ResponseResult getTrain(@RequestParam("tnum") String train_number){
        try {
            Train train = trainService.getTrainbyTrainnumber(train_number);
            if(train == null){
                return new ResponseResult<>("get Train failed");
            }else{
                return new ResponseResult<>(train);
            }
        }catch (Exception e){
            LOG.info("getTrainError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getTrainError");
    }

    //展示火车详细信息，包括车次，途径站点，时间，票价等
    @RequestMapping("/TrainInfo")
    public ResponseResult showTrainInfo(String train_number){
        try {
            Train train = trainService.getTrainbyTrainnumber(train_number);
            if(train == null){
                return new ResponseResult<>("get Traininfo failed");
            }else{
                Route route = new Route();
                List<Trainsit> trainsits = trainsitService.getTrainsitbyTrain(train_number);
                List<Seatprice> seatprices = seatpriceService.getSeatpricebyTrain(train_number);
                route = toRoute.ParsetoRoute(trainsits,seatprices);
                return new ResponseResult<>(route);
            }
        }catch (Exception e){
            LOG.info("getTraininfoError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("getTraininfoError");
    }

    //添加车次，仅添加基本信息
    @RequestMapping("/addTrain")
    public ResponseResult addTrain(Train train){
        try {
            Train train1 = trainService.getTrainbyTrainnumber(train.getTrain_number());
            if(train1 != null){
                return new ResponseResult<>("Train already exists");
            }else{
                trainService.addTrain(train1);
                return new ResponseResult<>("add Train Success");
            }
        }catch (Exception e){
            LOG.info("addTrainError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("addTrainError");
    }

    //删除车次，包括其所有信息
    @RequestMapping("/deleteTrain")
    public ResponseResult deleteTrain(Train train){
        try {
            Train train1 = trainService.getTrainbyTrainnumber(train.getTrain_number());
            if(train1 == null){
                return new ResponseResult<>("Train already deleted");
            }else{
                trainService.deleteTrain(train1.getTrain_number());
                List<Trainsit> trainsits = trainsitService.getTrainsitbyTrain(train1.getTrain_number());
                List<Seatprice> seatprices = seatpriceService.getSeatpricebyTrain(train1.getTrain_number());
                for(int i = 0;i < trainsits.size();i++){
                    trainsitService.deleteTrainsit(trainsits.get(i).getTrain_number(),trainsits.get(i).getStation_name());
                    seatpriceService.deleteSeatprice(seatprices.get(i).getTrain_number(),seatprices.get(i).getStation_name());
                }
                return new ResponseResult<>("delete Train Success");
            }
        }catch (Exception e){
            LOG.info("deleteTrainError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("deleteTrainError");
    }

    //规划火车路线
    @RequestMapping("/operateTrainRoute")
    public ResponseResult operateTrainRoute(Route route){
        try {
            Train train1 = trainService.getTrainbyTrainnumber(route.getTrain_number());
            List<Trainsit> trainsits = ToRoute.ParseToTrainsits(route);
            List<Seatprice> seatprices = ToRoute.ParseToSeatprices(route);
            if(train1 == null){
                for(int i = 0;i < trainsits.size();i++){
                    trainsitService.addTrainsit(trainsits.get(i));
                    seatpriceService.addSeatprice(seatprices.get(i));
                }
                Train train = new Train(route.getTrain_number(),trainsits.get(0).getStation_name(),trainsits.get(trainsits.size()-1).getStation_name(),trainsits.get(0).getArrival_time(),trainsits.get(trainsits.size()-1).getArrival_time());
                trainService.addTrain(train);
                return new ResponseResult<>("add TrainRoute Success");
            }else{
                for(int i = 0;i < trainsits.size();i++){
                    trainsitService.updateTrainsit(trainsits.get(i));
                    seatpriceService.updateSeatprice(seatprices.get(i));
                }
                return new ResponseResult<>("update TrainRoute Success");
            }
        }catch (Exception e){
            LOG.info("deleteTrainError:" + e);
            e.printStackTrace();
        }
        return new ResponseResult<>("deleteTrainError");
    }

}
