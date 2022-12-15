package com.example.train.util;

import com.example.train.pojo.Seatprice;
import com.example.train.pojo.Trainsit;
import com.example.train.vo.Route;

import java.sql.Time;
import java.sql.Timestamp;
import java.util.*;


/**
 * @author Sherlock Xu
 * @create 2022-12-12 13:24
 */
public class ToRoute {
    private List<String> stations;
    private List<Timestamp> arrival_times;
    private List<Time> stayed_times;
    private List<Map<String,Integer>> tickets;

    public Route ParsetoRoute(List<Trainsit> trainsits, List<Seatprice> seatprices){
        Route route = new Route();
        trainsits.sort(Comparator.comparing(Trainsit::getStation_order));
        seatprices.sort(Comparator.comparing(Seatprice::getStation_order));
        route.setTrain_number(trainsits.get(0).getTrain_number());
        for(Trainsit trainsit:trainsits){
            stations.add(trainsit.getStation_name());
            arrival_times.add(trainsit.getArrival_time());
            stayed_times.add(trainsit.getStay_time());
        }
        for(Seatprice seatprice:seatprices){
            Map<String,Integer> ticket = new HashMap<>();
            ticket.put("principal_seat",seatprice.getPrincipal_seat());
            ticket.put("first_seat",seatprice.getFirst_seat());
            ticket.put("second_seat",seatprice.getSecond_seat());
            ticket.put("hard_sleeper",seatprice.getHard_sleeper());
            ticket.put("soft_sleeper",seatprice.getSoft_sleeper());
            ticket.put("no_seat",seatprice.getNo_seat());
            ticket.put("principal_seat_price",seatprice.getPrincipal_seat_price());
            ticket.put("first_seat_price",seatprice.getFirst_seat_price());
            ticket.put("second_seat_price",seatprice.getSecond_seat_price());
            ticket.put("hard_sleeper_price",seatprice.getHard_sleeper_price());
            ticket.put("soft_sleeper_price",seatprice.getSoft_sleeper_price());
            ticket.put("no_seat_price",seatprice.getNo_seat_price());
            tickets.add(ticket);
        }
        return route;
    }

    public static List<Trainsit> ParseToTrainsits(Route route){
        Trainsit trainsit = new Trainsit();
        trainsit.setTrain_number(route.getTrain_number());
        List<Trainsit> trainsits = new ArrayList<>();
        for(int i = 0;i < route.getStations().size();i++){
            trainsit.setStation_name(route.getStations().get(i));
            trainsit.setStation_order(i);
            trainsit.setArrival_time(route.getArrival_times().get(i));
            trainsit.setStayed_time(route.getStayed_times().get(i));
            trainsits.add(trainsit);
        }
        return trainsits;
    }

    public static List<Seatprice> ParseToSeatprices(Route route){
        Seatprice seatprice = new Seatprice();
        seatprice.setTrain_number(route.getTrain_number());
        List<Seatprice> seatprices = new ArrayList<>();
        for(int i = 0;i < route.getTickets().size();i++){
            seatprice.setStation_name(route.getStations().get(i));
            seatprice.setStation_order(i);
            seatprice.setPrincipal_seat(route.getTickets().get(i).get("principal_seat"));
            seatprice.setFirst_seat(route.getTickets().get(i).get("first_seat"));
            seatprice.setSecond_seat(route.getTickets().get(i).get("second_seat"));
            seatprice.setHard_sleeper(route.getTickets().get(i).get("hard_sleeper"));
            seatprice.setSoft_sleeper(route.getTickets().get(i).get("soft_sleeper"));
            seatprice.setNo_seat(route.getTickets().get(i).get("no_seat"));
            seatprice.setPrincipal_seat_price(route.getTickets().get(i).get("principal_seat_price"));
            seatprice.setFirst_seat_price(route.getTickets().get(i).get("first_seat_price"));
            seatprice.setSecond_seat_price(route.getTickets().get(i).get("second_seat_price"));
            seatprice.setHard_sleeper_price(route.getTickets().get(i).get("hard_sleeper_price"));
            seatprice.setSoft_sleeper_price(route.getTickets().get(i).get("soft_sleeper_price"));
            seatprice.setNo_seat_price(route.getTickets().get(i).get("no_seat_price"));
            seatprices.add(seatprice);
        }
        return seatprices;
    }
}
