package com.trainsystem.result;

/**
 * @author Sherlock Xu
 * @create 2022-12-05 10:59
 */
public class Result {
    //响应码
    private int code;

    public Result(int code) {
        this.code = code;
    }

    public int getCode() {
        return code;
    }

    public void setCode(int code) {
        this.code = code;
    }

}
