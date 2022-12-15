package com.example.train.mapper;

import com.example.train.pojo.Distance;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:51
 */
@Mapper
public interface DistanceMapper {
    /**
     * 查询距离列表
     */
    @Select("select * from distance")
    List<Distance> getAllDistance();
    /**
     * 根据站点名称查询站点间距离
     */
    @Select("select * from distance where station_name1=#{station_name1} and station_name2=#{station_name2} or station_name1=#{station_name2} and station_name2=#{station_name1}")
    Distance getDistancebyStationnames(String station_name1,String station_name2);

    @Select("select * from distance where station_name1=#{station_name} or station_name2=#{station_name}")
    List<Distance> getDistancebyStationname(String station_name);
    /**
     * 插入站点距离信息
     */
    @Insert("insert into distance values(#{station_name1},#{station_name2},#{distance})")
    void addDistance(Distance distance);
    /**
     * 更新站点距离信息
     */
    @Update("update distance set distance=#{distance} where station_name1=#{station_name1} and station_name2=#{station_name2} or station_name1=#{station_name2} and station_name2=#{station_name1}")
    void updateDistance(Distance distance);
    /**
     * 删除站点距离
     */
    @Delete("delete from distance where station_name1=#{station_name1} and station_name2=#{station_name2} or station_name1=#{station_name2} and station_name2=#{station_name1}")
    void deleteDistance(Distance distance);
}
