package acmdb;

import java.sql.ResultSet;
import java.util.ArrayList;

/**
 * Created by were on 16/6/7.
 */
public class POI implements Row {
    public int pid;
    public String pname;
    public String address;
    public String phoneNo;
    public int yearEstablish;
    public String category;
    public String url;
    public String operation;
    public double price;
    public POI() {

    }

    public POI(int pid, String pname, String address, String phoneNo, int yearEstablish, String category, String url, String operation, double price) {
        this.pid = pid;
        this.pname = pname != null ? pname : "";
        this.address = address != null ? address : "";
        this.phoneNo = phoneNo != null ? phoneNo : "";
        this.yearEstablish = yearEstablish;
        this.category = category != null ? category : "";
        this.url = url != null ? url : "";
        this.operation = operation != null ? operation : "";
        this.price = price;
    }

    public static ArrayList<Row> fetch(String condition) {
        ResultSet set;
        try {
            String sql;
            if (!condition.equals("")) {
                sql = "SELECT * FROM POI WHERE " + condition;
            } else {
                sql = "SELECT * FROM POI";
            }
            Connector connector = new Connector();
            set = connector.stmt.executeQuery(sql);
            ArrayList<Row> res = new ArrayList<Row>();
            while (set.next()) {
                res.add(
                        new POI(
                                set.getInt("pid"),
                                set.getString("pname"),
                                set.getString("address"),
                                set.getString("phone_no"),
                                set.getInt("year_estab"),
                                set.getString("category"),
                                set.getString("url"),
                                set.getString("operation"),
                                set.getDouble("price")
                        )
                );
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String updatePOI(POI poi) {
        String sql;
        try {
            int exist = fetch("pid=" + Integer.toString(poi.pid)).size();
            if (exist == 0) {
                if (poi.pid == -1) {
                    sql = String.format("INSERT INTO POI (pname, address, phone_no, year_estab, category, url, operation, price)" +
                                    " VALUES " +
                                    "('%s', '%s', '%s', %d, '%s', '%s', '%s', %f);",
                            Util.toSQLString(poi.pname),
                            Util.toSQLString(poi.address),
                            Util.toSQLString(poi.phoneNo),
                            poi.yearEstablish,
                            Util.toSQLString(poi.category),
                            Util.toSQLString(poi.url),
                            Util.toSQLString(poi.operation), poi.price
                    );
                } else {
                    return "PIDCannotBeSpecified";
                }
            } else {
                sql = String.format(
                    "UPDATE POI SET pname='%s', address='%s', phone_no='%s', year_estab=%d, category='%s', url='%s', operation='%s', price='%f' WHERE pid=%d",
                    Util.toSQLString(poi.pname), Util.toSQLString(poi.address),
                        Util.toSQLString(poi.phoneNo), poi.yearEstablish, Util.toSQLString(poi.category),
                        Util.toSQLString(poi.url), Util.toSQLString(poi.operation), poi.price, poi.pid
                );
            }
        } catch (Exception e) {
            e.printStackTrace();
            System.out.println("SQL Error?");
            return "SQLError";
        }
        try {
            System.out.println(sql);
            Connector connector = new Connector();
            connector.stmt.execute(sql);
            System.out.println("Success!");
            connector.closeStatement();
            connector.closeConnection();
            return "success";
        } catch (Exception T_T) {
            T_T.printStackTrace();
            return "addFail";
        }
    }

    public static String addKeyword(int pid, String keyword) {
        if (fetch(String.format("pid=%d", pid)).size() == 0) {
            return "error=noSuchPOI";
        }
        try {
            System.out.println(String.format("INSERT INTO HasKeyword VALUES (%d, %s)", pid, Util.toSQLString(keyword)));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("INSERT INTO HasKeyword VALUES (%d, '%s')", pid, Util.toSQLString(keyword)));
            connector.closeStatement();
            connector.closeConnection();
        }
        catch (Exception e) {
            e.printStackTrace();
            return "error=SQLFail";
        }
        return "success";
    }

    public static String eraseKeyword(int pid, String keyword) {
        if (fetch(String.format("pid=%d", pid)).size() == 0) {
            return "error=noSuchPOI";
        }
        try {
            System.out.println(String.format("DELETE FROM HasKeyword WHERE pid=%d AND word='%s'", pid, keyword));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("DELETE FROM HasKeyword WHERE pid=%d AND word='%s'", pid, keyword));
            connector.closeStatement();
            connector.closeConnection();
        }
        catch (Exception e) {
            e.printStackTrace();
            return "error=SQLFail";
        }
        return "success";
    }

    public static ArrayList<String> fetchKeyword(int pid) {
        try {
            ArrayList<String> res = new ArrayList<String >();
            System.out.println(String.format("SELECT word FROM HasKeyword WHERE pid=%d", pid));
            ResultSet set = new Connector().stmt.executeQuery(String.format("SELECT word FROM HasKeyword WHERE pid=%d", pid));
            while (set.next()) {
                res.add(set.getString("word"));
            }
            return res;
        }
        catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public String toJsonElement() {
        return Util.toJsonElement("pid", pid) + "," +
                Util.toJsonElement("pname", pname) + "," +
                Util.toJsonElement("address", address) + "," +
                Util.toJsonElement("phoneno", phoneNo) + "," +
                Util.toJsonElement("year", yearEstablish) + "," +
                Util.toJsonElement("category", category) + "," +
                Util.toJsonElement("url", url) + "," +
                Util.toJsonElement("operation", operation) + "," +
                Util.toJsonElement("price", price);
    }

}
