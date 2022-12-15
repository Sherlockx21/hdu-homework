package com.example.train.vo;

import com.example.train.pojo.Distance;
import com.example.train.util.DFS;

import java.util.*;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 16:14
 */
public class StationMap {
    // 顶点数量
    private int stationnum;
    // 边的数量
    private int trailnum;
    // 邻接表
    private List[] pass;

    // 构造一个含有stations个顶点的图，但是不含边
    public StationMap(int stationnum) {
        pass = new ArrayList[stationnum];
        for (int i = 0; i < stationnum; i++) {
            pass[stationnum] = new ArrayList<Integer>();
        }
        this.stationnum = stationnum;
    }


    public int getStationnum() {
        return stationnum;
    }

    public void setStationnum(int stationnum) {
        this.stationnum = stationnum;
    }

    public int getTrailnum() {
        return trailnum;
    }

    public void setTrailnum(int trailnum) {
        this.trailnum = trailnum;
    }

    //添加边
    public void addtrails(int station1, int station2){
        pass[station1].add(station2);
        pass[station2].add(station1);
        this.trailnum++;
    }

    public void removetrails(int station1,int station2){
        pass[station1].remove(station2);
        pass[station2].remove(station1);
        this.trailnum--;
    }

    //获得与v相邻的所有顶点
    public Iterable<Integer> pass(int v){
        return pass[v];
    }

     //与结点s相连通的所有结点
    public Iterable<Integer> search(int v){
        DFS dfs = new DFS(this,v);
        List list = new ArrayList(dfs.getCount());
        for (int i=0;i<this.getStationnum();i++) {
            if (dfs.getMarked(i)){
                list.add(i);
            }
        }
        return list;
    }

    //是否存在station1结点到station2结点的路径
    public boolean reachable(int station1,int station2){
        DFS path = new DFS(this,station1);
        return path.reachable(station2);
    }

}
