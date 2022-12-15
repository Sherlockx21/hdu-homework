package com.example.train.util;

import com.example.train.vo.StationMap;

/**
 * @author Sherlock Xu
 * @create 2022-12-12 16:50
 */
public class DFS {
    private boolean[] marked;
    private int count;

    public DFS(StationMap stationmap, int s){
        marked = new boolean[stationmap.getStationnum()];
        dfs(stationmap,s);
    }

    private void dfs(StationMap stationmap, int s) {
        marked[s] = true;
        count++;
        for (int v:stationmap.pass(s)){
            if (!marked[v]){
                dfs(stationmap,v);
            }
        }
    }

    public boolean getMarked(int w) {
        return marked[w];
    }

    public int getCount() {
        return count;
    }

    public boolean reachable(int s){
        return getMarked(s);
    }
}
