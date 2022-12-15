package com.trainsystem.utils;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * @author Sherlock Xu
 * @create 2022-12-07 20:18
 */
public class TimeUtil {

    static SimpleDateFormat simpleFormat = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");

    public static String getTime() {
        return simpleFormat.format(new Date());
    }

    public static long getTimeLong() {
        return System.currentTimeMillis();
    }

}
