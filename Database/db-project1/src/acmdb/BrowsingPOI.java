package acmdb;

import java.beans.Statement;
import java.rmi.server.UID;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;

/**
 * Created by were on 16/6/9.
 */
public class BrowsingPOI extends POI {
    public double avgTrust, avgScore;
    static final String sqlFormat = "SELECT * FROM POI P";
    public BrowsingPOI(int pid, String pname, String address, String phoneNo, int yearEstablish, String category, String url, String operation, double price, double avgScore, double avgTrust) {
        super(pid, pname, address, phoneNo, yearEstablish, category, url, operation, price);
        this.avgScore = avgScore;
        this.avgTrust = avgTrust;
    }
    public BrowsingPOI(int pid, String pname, String address, String phoneNo, int yearEstablish, String category, String url, String operation, double price) {
        super(pid, pname, address, phoneNo, yearEstablish, category, url, operation, price);
    }
    static class ComparePriceAsc implements Comparator {
        public int compare(Object a, Object b) {
            return Util.sign(((BrowsingPOI) a).price - ((BrowsingPOI) b).price);
        }
    }
    static class ComparePriceDesc implements Comparator {
        public int compare(Object a, Object b) {
            return -Util.sign(((BrowsingPOI) a).price - ((BrowsingPOI) b).price);
        }
    }
    static class CompareBestFeedback implements Comparator {
        public int compare(Object a, Object b) {
            return -Util.sign(((BrowsingPOI) a).avgScore - ((BrowsingPOI) b).avgScore);
        }
    }
    static class CompareTrustedFeedback implements Comparator {
        public int compare(Object a, Object b) {
            return -Util.sign(((BrowsingPOI) a).avgTrust - ((BrowsingPOI) b).avgTrust);
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
                Util.toJsonElement("price", price) + "," +
                Util.toJsonElement("avg", avgScore) + "," +
                Util.toJsonElement("trust", avgTrust);
    }
}
