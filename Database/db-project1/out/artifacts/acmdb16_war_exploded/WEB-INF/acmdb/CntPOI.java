package acmdb;

/**
 * Created by were on 16/6/11.
 */
public class CntPOI extends POI {
    public int cnt;
    public CntPOI(int pid, String pname, String address, String phoneNo, int yearEstablish, String category, String url, String operation, double price, int cnt) {
        super(pid, pname, address, phoneNo, yearEstablish, category, url, operation, price);
        this.cnt = cnt;
    }
    public String toJsonElement() {
        return super.toJsonElement() + ", " + Util.toJsonElement("cnt", cnt);
    }
}
