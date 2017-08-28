package acmdb;

/**
 * Created by were on 16/6/11.
 */
public class AveragePOI extends POI{
    double avg;
    public AveragePOI(int pid, String pname, String address, String phoneNo, int yearEstablish, String category, String url, String operation, double price, double avg) {
        super(pid, pname, address, phoneNo, yearEstablish, category, url, operation, price);
        this.avg = avg;
    }

    @Override
    public String toJsonElement() {
        return super.toJsonElement() + "," + Util.toJsonElement("average", avg);
    }
}
