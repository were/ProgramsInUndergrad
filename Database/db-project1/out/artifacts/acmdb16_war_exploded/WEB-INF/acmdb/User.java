package acmdb;

import java.util.*;
import java.sql.*;

/**
 * Created by were on 16/6/7.
 */
public class User implements Row {

    public int uid;
    public String login;
    public String uname;
    public String phoneNo;
    public String pwd;
    public String address;

    public User() {
    }

    public User(int uid, String login, String uname, String phoneno, String pwd, String address) {
        this.uid = uid;
        this.login = login != null ? login : "";
        this.uname = uname != null ? uname : "";
        this.phoneNo = phoneno != null ? phoneno : "";
        this.pwd = pwd != null ? pwd : "";
        this.address = address != null ? address : "";
    }

    public static ArrayList<Row> fetch(String condition) {
        ResultSet data;
        try {
            if (condition.equals("")) {
                data = new Connector().stmt.executeQuery("SELECT * FROM User");
            } else {
                data = new Connector().stmt.executeQuery("SELECT * FROM User WHERE " + condition);
            }
            System.out.println("SELECT * FROM User WHERE " + condition);
            ArrayList<Row> res = new ArrayList<Row>();
            while (data.next()) {
                res.add(
                        new User(
                                data.getInt("uid"),
                                data.getString("login"),
                                data.getString("uname"),
                                data.getString("phone_no"),
                                data.getString("pwd"),
                                data.getString("address")
                        )
                );
            }
            return res;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static String login(String login, String password) {
        if (login == null || login.equals("")) {
            return "";
        }
        if (password == null || password.equals("")) {
            return "";
        }
        ArrayList<Row> users = fetch(String.format("login='%s'", login, password));
        if (users == null) {
            return "fetchError!";
        }
        if (users.size() == 0) {
            return "userNotFound=true";
        }
        for (Row user : users) {

            if (((User) user).pwd.equals(password)) {
                return "success";
            }
        }
        return "passwordError=true&login=" + login;
    }

    public String register() {
        if (login == "") {
            return "error=loginEmpty";
        }
        if (pwd == "") {
            return "error=pwdEmpty";
        }
        ArrayList<Row> users = fetch(String.format("login='%s'", login));
        if (users.size() != 0) {
            return "error=loginExisted";
        }
        try {
            new Connector().stmt.execute(String.format("insert into User (login, uname, phone_no, pwd, address) values ('%s', '%s', '%s', '%s', '%s');", Util.toSQLString(this.login), Util.toSQLString(this.uname), Util.toSQLString(this.phoneNo), Util.toSQLString(this.pwd), Util.toSQLString(this.address)));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "success";
    }

    public String toJsonElement() {
        return Util.toJsonElement("login", login) + "," +
                Util.toJsonElement("uname", uname) + "," +
                Util.toJsonElement("pwd", pwd) + "," +
                Util.toJsonElement("uid", uid) + "," +
                Util.toJsonElement("address", address) + "," +
                Util.toJsonElement("phoneno", phoneNo);
    }

    public String visit(POI poi, double cost, int cnt) {
        try {
            new Connector().stmt.execute(String.format("INSERT INTO Visit (uid, pid, cost, cnt) VALUES (%d, %d, %f, %d)", this.uid, poi.pid, cost, cnt));
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            return "sqlFail";
        }
    }

    public String like(POI poi) {
        try {
            System.out.println(String.format("INSERT INTO Favorite (uid, pid) VALUES (%d, %d)", this.uid, poi.pid));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("INSERT INTO Favorite (uid, pid) VALUES (%d, %d)", this.uid, poi.pid));
            connector.closeStatement();
            connector.closeConnection();
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            return "sqlFail";
        }
    }

    public boolean isLike(int pid) throws Exception {
        Connector connector = new Connector();
        if (connector.stmt.executeQuery(String.format("SELECT * FROM Favorite WHERE uid=%d AND pid=%d", this.uid, pid)).next()) {
            connector.closeStatement();
            connector.closeConnection();
            return true;
        } else {
            connector.closeStatement();
            connector.closeConnection();
            return false;
        }
    }

    public String feedback(POI poi, String comment, int score) {
        try {
            System.out.println(String.format("INSERT INTO Feedback (uid, pid, score, cmt) VALUES (%d, %d, %d, '%s')", this.uid, poi.pid, score, Util.toSQLString(comment)));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("INSERT INTO Feedback (uid, pid, score, cmt) VALUES (%d, %d, %d, '%s')", this.uid, poi.pid, score, Util.toSQLString(comment)));
            connector.closeStatement();
            connector.closeConnection();
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            return "sqlFail";
        }
    }

    public String opinion(int fid, int score) {
        try {
            System.out.println(String.format("INSERT INTO Opinion (fid, uid, score) VALUES (%d, %d, %d)", fid, this.uid, score));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("INSERT INTO Opinion (fid, uid, score) VALUES (%d, %d, %d)", fid, this.uid, score));
            connector.closeStatement();
            connector.closeConnection();
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            return "sqlFail";
        }
    }

    public String trust(User user, int trusted) {
        try {
            System.out.println(String.format(String.format("INSERT INTO Trust (from_uid, to_uid, rating) VALUES (%d, %d, %d)", this.uid, user.uid, trusted)));
            Connector connector = new Connector();
            connector.stmt.execute(String.format("INSERT INTO Trust (from_uid, to_uid, trusted) VALUES (%d, %d, %d)", this.uid, user.uid, trusted));
            connector.closeStatement();
            connector.closeConnection();
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            return "sqlFail";
        }
    }

    public ArrayList<Row> fetchPOI(double ge, double le, String address, String keyword, String category, String order) {
        String condition = "", sql;
        if (ge > 0.) {
            condition = Util.appendAndCondition(condition, String.format("P.price >= %f", ge));
        }
        if (le > 0.) {
            condition = Util.appendAndCondition(condition, String.format("P.price <= %f", le));
        }
        condition = Util.appendAndCondition(condition, Util.likeCluse("P.address", address));
        if (keyword != null && !"".equals(keyword))
            condition = Util.appendAndCondition(condition, "EXISTS (SELECT * FROM HasKeyword H WHERE H.pid=P.pid AND" + Util.likeCluse("H.word", keyword) + ")");
        condition = Util.appendAndCondition(condition, Util.likeCluse("P.category", category));
        sql = String.format("select P.*, t1.average1, t2.average2 from POI P left join (SELECT AVG(F.score) as average1, pid FROM Feedback F group by F.pid) t1 on P.pid = t1.pid left join (SELECT AVG(F.score) as average2, pid FROM Feedback F, Trust T where T.from_uid = %d and T.to_uid = F.uid and T.trusted = 1 group by F.pid) t2 on P.pid = t2.pid ", this.uid);
        if (condition.length() != 0) {
            sql += " WHERE " + condition;
        }
        if ("priceAsc".equals(order)) {
            sql += " ORDER BY p.price";
        } else if ("priceDesc".equals(order)) {
            sql += " ORDER BY p.price DESC";
        } else if ("bestFeedback".equals(order)) {
            sql += " ORDER BY average1 DESC";
        } else if ("trustedFeedback".equals(order)) {
            sql += " ORDER BY average2 DESC";
        }
        System.out.println(sql);
        try {
            Connector connector = new Connector();
            ResultSet condPOISet = connector.stmt.executeQuery(sql);
            ArrayList<Row> res = new ArrayList<Row>();
            while (condPOISet.next()) {
                BrowsingPOI cur = new BrowsingPOI(
                        condPOISet.getInt("pid"),
                        condPOISet.getString("pname"),
                        condPOISet.getString("address"),
                        condPOISet.getString("phone_no"),
                        condPOISet.getInt("year_estab"),
                        condPOISet.getString("category"),
                        condPOISet.getString("url"),
                        condPOISet.getString("operation"),
                        condPOISet.getDouble("price"),
                        condPOISet.getDouble("average1"),
                        condPOISet.getDouble("average2")
                );
                res.add(cur);
            }
            connector.closeStatement();
            connector.closeConnection();
            return res;
        }catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
