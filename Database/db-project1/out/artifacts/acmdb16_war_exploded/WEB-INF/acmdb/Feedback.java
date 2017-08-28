package acmdb;

import java.sql.ResultSet;
import java.util.ArrayList;

/**
 * Created by were on 16/6/10.
 */
public class Feedback implements Row{
    int uid;
    String from;
    int score;
    String cmt;
    double opinion;
    int fid;

    Feedback(int uid, String from, int score, String cmt, int fid, double opinion) {
        this.uid = uid;
        this.from = from;
        this.score = score;
        this.cmt = cmt;
        this.fid = fid;
        this.opinion = opinion;
    }

    @Override
    public String toJsonElement() {
        return Util.toJsonElement("from", from) + ", " +
                Util.toJsonElement("score", score) + ", " +
                Util.toJsonElement("cmt", cmt) + ", " +
                Util.toJsonElement("opinion", opinion) + ", " +
                Util.toJsonElement("uid", uid) + ", " +
                Util.toJsonElement("fid", fid);
    }

    static ArrayList<Row> stringToFeedbackArray(String sql) throws Exception {
        Connector connector = new Connector();
        ResultSet set = connector.stmt.executeQuery(sql);
        ArrayList<Row> res = new ArrayList<Row>();
        while (set.next()) {
            res.add(new Feedback(
                    set.getInt("uid"),
                    set.getString("uname"),
                    set.getInt("score"),
                    set.getString("cmt"),
                    set.getInt("fid"),
                    set.getDouble(6)
            ));
        }
        connector.closeStatement();
        connector.closeConnection();
        return res;
    }

    public static ArrayList<Row> fetch(int pid) {
        String sql = String.format("select U.uid, U.uname, F.fid, F.score, F.cmt, AVG(O.score) from User U, Feedback F left join Opinion O on O.fid=F.fid where U.uid=F.uid and F.pid=%d group by F.fid;", pid);
        try {
            return stringToFeedbackArray(sql);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public static ArrayList<Row> fetchUseful(int pid) {
        String sql = String.format("select User.uid, User.uname, Feedback.fid, Feedback.score, Feedback.cmt, t.average from User, Feedback,(select sum(score)/count(*) as average, fid from Opinion group by fid) t where User.uid=Feedback.uid and Feedback.fid = t.fid and Feedback.pid = %d order by t.average desc limit 0, 5", pid);
        try {
            return stringToFeedbackArray(sql);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
         }
    }
}
