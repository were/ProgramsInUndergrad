package acmdb;

/**
 * Created by were on 16/6/11.
 */

/**
 * Created by Mars on 2016/6/10.
 */


import javafx.util.Pair;
import java.sql.ResultSet;
import java.util.ArrayList;

public class MHJ {
    public static int m_POI = 5;
    public static int m_User = 5;
    public static ArrayList<Row> suggest(int pid){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select p.*, count(*) as cnt from (select distinct v2.uid, v2.pid from Visit v1, Visit v2 where v1.pid = %d and v2.pid != %d and v2.uid = v1.uid) as t, POI p where t.pid = p.pid group by t.pid order by count(*) desc", pid, pid));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new CntPOI(
                                data.getInt("pid"),
                                data.getString("pname"),
                                data.getString("address"),
                                data.getString("phone_no"),
                                data.getInt("year_estab"),
                                data.getString("category"),
                                data.getString("url"),
                                data.getString("operation"),
                                data.getDouble("price"),
                                data.getInt("cnt")
                ));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchPopularPOI(){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select p1.*, t1.cnt from (select count(*) as cnt, pid from Visit group by pid) as t1, POI p1 where t1.pid = p1.pid and %d > (select count(*) from (select count(*) as cnt, pid from Visit group by pid) as t2, POI p2 where t2.pid = p2.pid and p2.category = p1.category and t2.cnt > t1.cnt) order by p1.category, t1.cnt desc;", m_POI));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new CntPOI(
                                data.getInt("pid"),
                                data.getString("pname"),
                                data.getString("address"),
                                data.getString("phone_no"),
                                data.getInt("year_estab"),
                                data.getString("category"),
                                data.getString("url"),
                                data.getString("operation"),
                                data.getDouble("price"),
                                data.getInt("cnt")));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchExpensivePOI(){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select p1.*, t1.average from POI p1, (select sum(cost)/sum(cnt) as average, pid from Visit group by pid) t1 where p1.pid = t1.pid and %d > (select count(*) from POI p2, (select sum(cost)/sum(cnt) as average, pid from Visit group by pid) t2 where p2.pid = t2.pid and p2.category = p1.category and t2.average > t1.average) order by p1.category, t1.average desc;", m_POI));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new AveragePOI(
                                data.getInt("pid"),
                                data.getString("pname"),
                                data.getString("address"),
                                data.getString("phone_no"),
                                data.getInt("year_estab"),
                                data.getString("category"),
                                data.getString("url"),
                                data.getString("operation"),
                                data.getDouble("price"),
                                data.getDouble("average")));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchHighRatedPOI(){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select p1.*, t1.average from POI p1, (select sum(score)/count(*) as average, pid from Feedback group by pid) t1 where p1.pid = t1.pid and %d > (select count(*) from POI p2, (select sum(score)/count(*) as average, pid from Feedback group by pid) t2 where p2.pid = t2.pid and p2.category = p1.category and t2.average > t1.average) order by p1.category, t1.average desc;", m_POI));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new AveragePOI(
                                data.getInt("pid"),
                                data.getString("pname"),
                                data.getString("address"),
                                data.getString("phone_no"),
                                data.getInt("year_estab"),
                                data.getString("category"),
                                data.getString("url"),
                                data.getString("operation"),
                                data.getDouble("price"),
                                data.getDouble("average")));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchMostTrustedUser(){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select User.*, SUM(trusted) as sum from Trust, User where Trust.to_uid = User.uid group by to_uid order by SUM(trusted) desc limit 0, %d;", m_User));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new CntUser(
                                data.getInt("uid"),
                                data.getString("login"),
                                data.getString("uname"),
                                data.getString("phone_no"),
                                "",
                                data.getString("address"),
                                data.getInt("sum")));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchMostUsefulUser(){
        ResultSet data;
        try {
            Connector connector = new Connector();
            data = connector.stmt.executeQuery(String.format("select u.*, sum(o.score)/count(*) as average from Opinion o, Feedback f, User u where o.fid = f.fid and f.uid = u.uid group by f.uid order by average desc limit 0, %d", m_User));
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(new AvgUser(
                                data.getInt("uid"),
                                data.getString("login"),
                                data.getString("uname"),
                                data.getString("phone_no"),
                                "",
                                data.getString("address"),
                                data.getDouble("average")));
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
