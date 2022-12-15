package com.example.train.util;

import com.example.train.pojo.Trainsit;
import com.example.train.vo.StationBoard;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 14:44
 */
public class ToStationBoard {
    private String station_name;
    private String city_name;
    private List<String> train_numbers;
    private List<Timestamp> arrivaltimes;
    private List<Time> stayed_times;

    public StationBoard ParsetoStationBoard(List<Trainsit> trainsits){
        StationBoard stationBoard = new StationBoard();
        for(Trainsit trainsit:trainsits){
            train_numbers.add(trainsit.getStation_order(),trainsit.getTrain_number());
            arrivaltimes.add(trainsit.getStation_order(),trainsit.getArrival_time());
            stayed_times.add(trainsit.getStation_order(),trainsit.getStay_time());
        }
        stationBoard.setTrain_numbers(train_numbers);
        stationBoard.setArrivaltimes(arrivaltimes);
        stationBoard.setStayed_times(stayed_times);
        return stationBoard;
    }
}
