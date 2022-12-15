package com.example.train.service;

import com.example.train.pojo.Trainsit;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:24
 */
public interface TrainsitService {
    public List<Trainsit> getAllTrainsits();
    public Trainsit getTrainsit(String train_number,String station_name);
    public List<Trainsit> getTrainsitbyTrain(String train_number);
    public List<Trainsit> getTrainsitbyStation(String station_name);
    public void addTrainsit(Trainsit trainsit);
    public void updateTrainsit(Trainsit trainsit);
    public void deleteTrainsit(String train_number,String station_name);
    public void deleteStation(String station_name);
}
