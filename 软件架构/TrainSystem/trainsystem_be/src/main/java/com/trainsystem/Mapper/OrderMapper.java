package com.trainsystem.Mapper;

import com.trainsystem.entity.Order;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 19:01
 */
public interface OrderMapper {

    // 乘客购票下单
    @Insert("NSERT INTO t_order VALUES (NULL,#{uid},#{pid},#{tid},#{s_start},#{startTime},#{s_end},#{endTime},#{createTime},#{stype},#{money},#{otype},0)")
    void addOrder(Order order);

    // 查询某用户下的所有票
    @Select("SELECT * FROM t_order WHERE uid =#{uid} AND del=0")
    List<Order> findAllOrderByUid(int uid);

    // 根据订单状态查票
    @Select("SELECT * FROM t_order WHERE otype = #{otype} AND del=0")
    List<Order> findOrderByOtype(int otype);

    // 根据订单id查票
    @Select("SELECT * FROM t_order WHERE oid = #{oid} AND del=0")
    Order findOrderByOid(int id);

    // 取消订单
    @Update("UPDATE t_order SET del = 1 WHERE oid = #{oid} ")
    void deleteOrderByOid(int id);

    // 改变订单状态：付款
    @Update("UPDATE t_order SET otype = 1 WHERE oid = #{oid} AND del=0")
    void OtypeToPay(int id);

    // 改变订单状态：出票
    @Update("UPDATE t_order SET otype = 2 WHERE oid = #{oid} AND del=0")
    void OtypeToPost(int id);

    // 根据pid查name
    String findNameByUid(int pid);

}

