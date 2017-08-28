package acmdb;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Iterator;

/**
 * Created by were on 16/6/7.
 */
public class Util {
    public static String toJsonElement(String a, int b) {
        return "\"" + a + "\"" + " : " + Integer.toString(b);
    }

    public static String toJsonElement(String a, double b) {
        return "\"" + a + "\"" + " : " + Double.toString(b);
    }

    public static String toJsonElement(String a, String b) {
        return "\"" + a + "\"" + " : " + "\"" + b + "\"";
    }

    public static String arrayToJson(ArrayList<Row> rows) {
        Iterator iter = rows.iterator();
        String res = " [ ";
        while (iter.hasNext()) {
            Row cur = (Row) iter.next();
            if (iter.hasNext()) {
                res += " { " + cur.toJsonElement() + " }, ";
            } else {
                res += " { " + cur.toJsonElement() + " } ";
            }
        }
        return res + " ] ";
    }

    public static String toJsonElement(String a, ArrayList<Row> rows) {
        return "\"" + a + "\":" + arrayToJson(rows);
    }

    public static String appendAndCondition(String a, String b) {
        if (a.length() == 0) {
            return b;
        }
        if (b.length() == 0) {
            return a;
        }
        return a + " AND " + b;
    }

    public static int sign(double a) {
        if (a < -1e-15) {
            return -1;
        }
        return a > 1e-15 ? 1 : 0;
    }

    public static double getTheOnlyDouble(ResultSet res) throws SQLException {
        if (res.next()) {
            return res.getDouble(1);
        }
        return 0;
    }

    public static String likeCluse(String attr, String substring) {
        if (substring == null || substring.length() == 0) {
            return "";
        }
        return " " + attr + " like '%" + substring + "%' ";
    }

    public static String toSQLString(String s) {
        System.out.println(s);
        System.out.println(s.replaceAll("'", "\\'"));
        return s.replaceAll("'", "\\\\'").replaceAll("\"", "\\\\\"");
    }
}
