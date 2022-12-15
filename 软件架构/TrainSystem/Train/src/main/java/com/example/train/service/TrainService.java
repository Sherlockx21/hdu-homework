package com.example.train.service;

import com.example.train.pojo.Train;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:27
 */
public interface TrainService{
    public List<Train> getAllTrains();
    public List<String> getAllTrainnumber();
    public Train getTrainbyTrainnumber(String train_number);
    public void addTrain(Train train);
    public void updateTrain(Train train);
    public void deleteTrain(String train_number);
    public void refresh(String train_number);

}
