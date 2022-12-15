package com.example.train;

import com.example.train.controller.StationController;
import com.example.train.controller.TrainController;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class TrainApplicationTests {
    @Resource
    private TrainController trainController;
    @Resource
    private StationController stationController;
    @Test
    void traincontrollertest(){
        System.out.println(trainController.getTrainList().toString());
    }


}
