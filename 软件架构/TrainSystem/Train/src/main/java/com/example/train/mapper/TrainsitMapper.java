package com.example.train.mapper;

import com.example.train.pojo.Trainsit;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:24
 */
@Mapper
public interface TrainsitMapper {
    /**
     * 查询车站列表
     */
    @Select("select * from trainsit")
    List<Trainsit> getAllTrainsits();
    /**
     * 根据站点名称查询站点
     */
    @Select("select * from trainsit where train_number=#{train_number} and station_name=#{station_name}")
    Trainsit getTrainsit(String train_number,String station_name);

    @Select("select * from trainsit where train_number=#{train_number}")
    List<Trainsit> getTrainsitbyTrain(String train_number);

    @Select("select * from trainsit where station_name=#{station_name}")
    List<Trainsit> getTrainsitbyStation(String station_name);
    /**
     * 插入站点信息
     */
    @Insert("insert into trainsit values(#{train_number},#{station_name},#{station_order},#{arrival_time},#{stayed_time})")
    void addTrainsit(Trainsit trainsit);
    /**
     * 更新站点信息
     */
    @Update("update trainsit set station_order=#{station_order},arrival_time=#{arrival_time},stayed_time=#{stayed_time} where train_number=#{train_number} and station_name=#{station_name}")
    void updateTrainsit(Trainsit trainsit);
    /**
     * 删除站点
     */
    @Delete("delete from trainsit where train_number=#{train_number} and station_name=#{station_name}")
    void deleteTrainsit(String train_number,String station_name);
}
