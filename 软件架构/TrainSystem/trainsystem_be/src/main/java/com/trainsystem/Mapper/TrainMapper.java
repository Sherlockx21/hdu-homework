package com.trainsystem.Mapper;

import com.trainsystem.entity.Station;
import com.trainsystem.entity.Train;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 18:59
 */
public interface TrainMapper {

//    /**
//     * 根据车辆类型查询车辆编号列表
//     *
//     * @param ttype
//     * @return
//     */
//    @Select("select tid from trains where ttype=#{ttype}")
//    List<String> getTidListByType(String ttype) throws Exception;

    /**
     * 根据车辆信息查询车站信息
     *
     * @param train
     * @return
     */
    @Select("select * from station where")
    Station getStartInfo(Train train) throws Exception;// 获取出发站和出发时间

    Station getArriveInfo(Train train) throws Exception;// 获取终点站和到达时间

    /**
     * 获取所有车辆的编号
     *
     * @return
     * @throws Exception
     */
    @Select("select train_number from trains")
    List<String> getTidList() throws Exception;

    /**
     * 根据编号获取车辆信息
     *
     * @param tid
     * @return
     * @throws Exception
     */
    @Select("select * from trains where tid=#{tid}")
    Train getTrainInfoById(String tid) throws Exception;

    /**
     * 新增车辆
     *
     * @param train
     * @return
     * @throws Exception
     */
    @Insert("insert into trains values(#{tid},#{stype1},#{scount1},#{tmoney1},#{stype2},#{scount2},#{tmoney2},#{stype3},#{scount3},#{tmoney3},#{runtime},#{stacount},0")
    void addnewtrain(Train train) throws Exception;

    /**
     * 改变座位类型1
     *
     * @param train
     * @return
     * @throws Exception
     */
    @Update("update trains set stype1=#{stype1},tmoney1=#{tmoney1} where tid=#{tid}")
    void updateTrainSeatType1(Train train) throws Exception;
    @Update("update trains set stype2=#{stype2},tmoney2=#{tmoney2} where tid=#{tid}")
    void updateTrainSeatType2(Train train) throws Exception;
    @Update("update trains set stype3=#{stype3},tmoney3=#{tmoney3} where tid=#{tid}")
    void updateTrainSeatType3(Train train) throws Exception;

}

