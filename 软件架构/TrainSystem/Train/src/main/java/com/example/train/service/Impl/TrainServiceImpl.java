package com.example.train.service.Impl;

import com.example.train.mapper.TrainMapper;
import com.example.train.mapper.TrainsitMapper;
import com.example.train.pojo.Train;
import com.example.train.pojo.Trainsit;
import com.example.train.service.TrainService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Comparator;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:27
 */
@Service
public class TrainServiceImpl implements TrainService {
    @Resource
    private TrainMapper trainMapper;
    @Resource
    private TrainsitMapper trainsitMapper;
    @Resource
    private Train train;

    private List<Train> trains;
    @Override
    public List<Train> getAllTrains(){
        trains = trainMapper.getAllTrains();
        return trains;
    }
    @Override
    public Train getTrainbyTrainnumber(String train_number){
        train = trainMapper.getTrainbyTrainnumber(train_number);
        return train;
    }
    @Override
    public void addTrain(Train train){
        trainMapper.addTrain(train);
    }
    @Override
    public void updateTrain(Train train){
        trainMapper.updateTrain(train);
    }
    @Override
    public void deleteTrain(String train_number){
        trainMapper.deleteTrain(train_number);
    }
    @Override
    public List<String> getAllTrainnumber(){
        List<String> train_numbers = trainMapper.getAllTrainnumber();
        return train_numbers;
    }
    @Override
    public void refresh(String train_number){
        train = trainMapper.getTrainbyTrainnumber(train_number);
        List<Trainsit> trainsits = trainsitMapper.getTrainsitbyTrain(train_number);
        trainsits.sort(Comparator.comparing(Trainsit::getStation_order));
        Trainsit trainsit = trainsits.get(0);
        train.setStart_station(trainsit.getStation_name());
        train.setStart_time(trainsit.getArrival_time());
        trainsit = trainsits.get(trainsits.size()-1);
        train.setEnd_station(trainsit.getStation_name());
        train.setEnd_time(trainsit.getArrival_time());
        updateTrain(train);
    }
}
