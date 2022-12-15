package com.example.train.mapper;

import com.example.train.pojo.Train;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:27
 */
@Mapper
public interface TrainMapper{
    /**
     * 查询车辆列表
     */
    @Select("select * from trains")
    List<Train> getAllTrains();
    /**
     * 根据车辆编号查询车辆
     */
    @Select("select * from trains where train_number=#{train_number}")
    Train getTrainbyTrainnumber(String train_number);
    /**
     * 插入新车信息
     */
    @Insert("insert into trains values(#{train_number},#{start_station},#{end_station},#{start_time},#{end_time})")
    void addTrain(Train train);
    /**
     * 更新火车信息
     */
    @Update("update trains set start_station=#{start_station},end_station=#{end_station},start_time=#{start_time},end_time=#{end_time} where train_number=#{train_number}")
    void updateTrain(Train train);
    /**
     * 删除车辆
     */
    @Delete("delete from trains where train_number=#{train_number}")
    void deleteTrain(String train_number);
    /**
     * 获取所有车辆编号
     */
    @Select("select train_number from trains")
    List<String> getAllTrainnumber();
}
