package com.example.train.util;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 8:33
 */
public class ResponseResult <T>{
    private Integer state;
    private String message;
    private T data;

    public ResponseResult(){
        super();
    }
    public ResponseResult(Integer state){
        super();
        this.state = state;
    }
    public ResponseResult(String message){
        super();
        this.message = message;
    }
    public ResponseResult(T data){
        super();
        this.data = data;
    }

    public Integer getState() {
        return state;
    }

    public void setState(Integer state) {
        this.state = state;
    }

    public String getMessage() {
        return message;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    public T getData() {
        return data;
    }

    public void setData(T data) {
        this.data = data;
    }
}
