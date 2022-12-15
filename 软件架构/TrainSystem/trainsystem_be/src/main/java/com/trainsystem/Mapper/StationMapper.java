package com.trainsystem.Mapper;

import com.trainsystem.entity.Station;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 18:59
 */
public interface StationMapper {

    /**
     * 根据车次编号获取车站列表信息
     *
     * @param tid
     * @return
     * @throws Exception
     */
    @Select("select * from trainsit where train_number=#{tid}")
    List<Station> getStationInfoByTid(String tid) throws Exception;

    /**
     * 获取符合出发站条件的车次编号列表
     *
     * @param sname1
     * @return
     */
    @Select("select tid from station where sname1=#{sname1}")
    List<String> getStartTidList(String sname1) throws Exception;

    /**
     * 获取符合到达站条件的车次编号列表
     *
     * @param sname2
     * @return
     */
    @Select("select tid from station where sname2=#{sname2}")
    List<String> getEndTidList(String sname2) throws Exception;

    /**
     * 新增车辆对应的车站
     *
     * @param station
     * @return
     */
    @Insert("insert into station values (#{tid},#{sname1},#{stime1},#{sname2},#{stime2},#{ticket},#{tmoney})")
    void addnewtrain(Station station) throws Exception;

    /**
     * 根据车辆tid，sname1改变站点的区间票数，价格
     *
     * @param station
     * @return
     */
    @Update("update station set ticket=#{ticket},tmoney=#{tmoney} where tid=#{tid} and sname1=#{sname1}")
    void updateStationByTrain(Station station) throws Exception;

    /**
     * 根据车辆tid，ticket,money 改变站点的区间票数，价格
     *
     * @param station
     * @return
     */
    @Update("update station set sname1=#{sname1},stime1=#{stime1},sname2=#{sname2},stime2=#{stime2} WHERE tid=#{tid} AND sname1=#{temp}")
    void changeStationList(Station station) throws Exception;

}
