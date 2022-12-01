package com.trainsystem.service;


import org.apache.ibatis.annotations.Result;


/**
 * @author Sherlock Xu
 * @create 2022-11-28 17:29
 */
public interface AdminService {
    Result Login(String account, String password);
}
