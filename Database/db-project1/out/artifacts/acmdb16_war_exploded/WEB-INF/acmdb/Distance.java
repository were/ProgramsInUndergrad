package acmdb;

/**
 * Created by Mars on 2016/6/10.
 */

import java.sql.*;
import java.util.*;

public class Distance {
    static public int dis(int a, int b){
        ResultSet data;
        int n = 0;

        try {
            data = new Connector().stmt.executeQuery("select max(uid) from User");
            if (data.next()) {
                n = data.getInt(1);
            } else {
                return -1;
            }
        } catch (Exception e) {
            e.printStackTrace();
            return -1;
        }

        if (a > n || b > n) return -1;

        int[] d = new int[n + 5];
        for (int i = 0; i <= n; i++) d[i] = n + 5;
        d[a] = 0;
        Queue<Integer> q = new LinkedList<Integer>();
        q.offer(a);

        while (q.peek() != null) {
            a = q.poll();
            try {
                data = new Connector().stmt.executeQuery("select f2.uid from Favorite f1, Favorite f2 where f1.pid = f2.pid and f1.uid = " + a);
                while (data.next()) {
                    int x = data.getInt("uid");
                    if (d[x] > d[a] + 1){
                        d[x] = d[a] + 1;
                        if (x == b) break;
                        q.offer(x);
                    }
                }
                if (d[b] < n + 5) return d[b];
            } catch (Exception e) {
                e.printStackTrace();
                return -1;
            }
        }
        return -1;
    }

}
