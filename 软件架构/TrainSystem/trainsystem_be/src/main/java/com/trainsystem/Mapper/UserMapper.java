package com.trainsystem.Mapper;

import com.trainsystem.entity.Passenger;
import com.trainsystem.entity.User;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 19:00
 */
public interface UserMapper {

    @Select("select username,phone,address from user where username = #{userName}")
    User findByName(String name) throws Exception;

    // 修改用户信息
    @Update("update user set phone=#{phone}, address=#{address} where uid =#{uid}")
    void updateUser(User user) throws Exception;

    // 修改密码
    @Update("update t_user set password=#{password} where uid=#{uid}")
    void updatePass(User user) throws Exception;

    @Select("select t1.pid,truename trueName,idcard,role from t_passenger t1,user_passenger t2 where t2.uid=#{uid} and t1.pid=t2.pid and del = 0")
    List<Passenger> findPassenger(int uid) throws Exception;

    @Insert("insert into t_passenger values(null,#{trueName},#{idCard},#{role},0)")
    int addpassenger(Passenger passenger) throws Exception;

    @Select("select pid,truename trueName,idcard,role from t_passenger where idCard = #{idCard} and del = 0")
    Passenger findPassengerId(String idCard) throws Exception;

    // 关联表
    @Insert("insert into user_passenger values(#{uid},#{passengerList[0].pid})")
    void userTopassenger(User user) throws Exception;

    int addUser(User user) throws Exception;

    void userfindpassenger(int uid, int pid) throws Exception;

    // 用户/管理员 登录校验
    @Select("SELECT * FROM t_user WHERE username=#{userName} AND password=#{password} AND utype=#{utype}")
    User loginCheck(User user) throws Exception;

    // 用户名唯一性校验
    @Select("SELECT * FROM t_user WHERE username=#{userName} AND utype=0")
    User nameCheck(String userName) throws Exception;

    @Select("select * from t_passenger where pid = #{pid} and del = 0")
    // 根据乘客id获取乘客信息
    Passenger findByid(int pid) throws Exception;

    // 根据用户id查用户信息
    @Select("select username,password,phone,address from t_user where uid = #{uid}")
    User findUserById(int uid) throws Exception;

    // 删除用户的某个乘客
    @Delete("DELETE FROM user_passenger WHERE uid=#{uid} AND pid=#{passengerList[0].pid}")
    void deletepassenger(User user) throws Exception;

    @Update("update t_passenger set role=#{role} where pid=#{pid}")
    void updateType(Passenger passenger) throws Exception;

}
