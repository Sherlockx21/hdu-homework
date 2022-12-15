package com.example.train.mapper;

import com.example.train.pojo.Station;
import org.apache.ibatis.annotations.*;
import org.springframework.stereotype.Component;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 21:45
 */
@Mapper
public interface StationMapper {
    @Results({
            @Result(property = "station_name", column = "station_name"),
            @Result(property = "city_name", column = "city_name")
    })
    /**
     * 查询车站列表
     */
    @Select("select * from station")
    List<Station> getAllStations();
    /**
     * 根据站点名称查询站点
     */
    @Select("select * from station where station_name=#{station_name}")
    Station getStationbyStationname(String station_name);
    /**
     * 插入站点信息
     */
    @Insert("insert into station values(#{station_name},#{city_name})")
    void addStation(Station station);
    /**
     * 更新站点信息
     */
    @Update("update station set city_name=#{city_name} where station_name=#{station_name}")
    void updateStation(Station station);
    /**
     * 删除站点
     */
    @Delete("delete from station where station_name=#{station_name}")
    void deleteStation(String station_name);
}
