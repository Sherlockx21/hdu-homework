package com.example.train.mapper;

import com.example.train.pojo.Seatprice;
import com.example.train.pojo.Station;
import org.apache.ibatis.annotations.*;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-11 22:12
 */
@Mapper
public interface SeatpriceMapper {
    /**
     * 查询价格和座位列表
     */
    @Select("select * from seat_price")
    List<Seatprice> getAllSeatprice();
    /**
     * 根据站点名称和车次查询价格和座位
     */
    @Select("select * from seat_price where train_number=#{train_number} and station_name=#{station_name}")
    Seatprice getSeatprice(String train_number,String station_name);

    @Select("select * from seat_price where train_number=#{train_number}")
    List<Seatprice> getSeatpricebyTrain(String train_number);

    @Select("select * from seat_price where station_name=#{station_name}")
    List<Seatprice> getSeatpricebyStation(String station_name);
    /**
     * 插入价格和座位信息
     */
    @Insert("insert into seat_price values(#{train_number},#{station_name},#{station_order},#{principal_seat},#{first_seat},#{second_seat},#{hard_sleeper},#{soft_sleeper},#{no_seat},#{principal_seat_price},#{first_seat_price},#{second_seat_price},#{hard_sleeper_price},#{soft_sleeper_price},#{no_seat_price})")
    void addSeatprice(Seatprice seatprice);
    /**
     * 更新站价格和座位
     */
    @Update("update seat_price set station_order=#{station_order},principal_seat=#{principal_seat},first_seat=#{first_seat},second_seat=#{second_seat},hard_sleeper=#{hard_sleeper},soft_sleeper=#{soft_sleeper},no_seat=#{no_seat},principal_seat_price=#{principal_seat_price},first_seat_price=#{first_seat_price},second_seat_price=#{second_seat_price},hard_sleeper_price=#{hard_sleeper_price},soft_sleeper_price=#{soft_sleeper_price},no_seat_price=#{no_seat_price} where train_number=#{train_number} and station_name=#{station_name}")
    void updateSeatprice(Seatprice seatprice);

    /**
     * 删除价格和座位
     */
    @Delete("delete from seat_price where station_name=#{station_name} and train_number=#{train_number}")
    void deleteSeatprice(String train_number,String station_name);
}
