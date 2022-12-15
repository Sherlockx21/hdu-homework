package com.example.train.service;

import com.example.train.pojo.Seatprice;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:12
 */
public interface SeatpriceService {
    public List<Seatprice> getAllSeatprice();
    public Seatprice getSeatprice(String train_number,String station_name);
    public List<Seatprice> getSeatpricebyTrain(String train_number);
    public List<Seatprice> getSeatpricebyStation(String station_name);
    public void addSeatprice(Seatprice seatprice);
    public void updateSeatprice(Seatprice seatprice);
    public void deleteSeatprice(String train_number,String station_name);
    public void deleteStation(String station_name);
}
