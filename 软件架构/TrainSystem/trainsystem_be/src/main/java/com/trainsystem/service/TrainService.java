package com.trainsystem.service;

import com.trainsystem.entity.Station;
import com.trainsystem.entity.Train;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 18:26
 */

public interface TrainService {

    /**
     * 根据车辆类型查询车辆列表
     *
     * @param tid
     * @return
     * @throws Exception
     */
    public List<Train> getTrainList(String tid) throws Exception;

    /**
     * 获取所有车辆的编号
     *
     * @return
     * @throws Exception
     */
    public List<String> getTidList() throws Exception;

    /**
     * 根据编号获取车辆信息
     *
     * @param tid
     * @return
     * @throws Exception
     */
    public Train getTrainInfoById(String tid) throws Exception;

    /**
     * 根据用户需求-出发站/到达站-查询车辆列表-出行路线
     *
     * @param sname1
     *            出发站
     * @param sname2
     *            到达站
     * @return
     * @throws Exception
     */
    public List<Train> getTrainRout(String sname1, String sname2) throws Exception;

    /**
     * 根据用户需求-出发站/到达站-查询车辆列表-出行路线--换乘的情况
     *
     * @param sname1
     *            出发站
     * @param sname2
     *            到达站
     * @return
     * @throws Exception
     */
    public List<Map<String, Object>> getTrainRout2(String sname1, String sname2) throws Exception;

    /**
     * 新增车辆
     *
     * @return
     * @throws Exception
     */
    public void addnewtrain(Train train) throws Exception;

    /**
     * 根据车辆编号查询途经的所有站点
     *
     * @return
     * @throws Exception
     */
    public List<Station> getStationListById(String tid) throws Exception;

    /**
     * 改变车辆 途经站点
     *
     * @return
     * @throws Exception
     */
    public void changeStationList(List<Station> list) throws Exception;

    /**
     * 改变车辆 途经站点的车票价格与数量
     *
     * @return
     * @throws Exception
     */
    public void updateStationByTrain(List<Station> listStation) throws Exception;

    /**
     * 根据车站编号改变火车座位类型与价格
     *
     * @return
     * @throws Exception
     */
    public void updateTrainSeatType1(Train train) throws Exception;

    public void updateTrainSeatType2(Train train) throws Exception;

    public void updateTrainSeatType3(Train train) throws Exception;

}
