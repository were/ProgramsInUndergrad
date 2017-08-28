package acmdb;

/**
 * Created by were on 16/6/11.
 */
public class AvgUser extends User {
    double avg;
    public AvgUser(int uid, String login, String uname, String phoneno, String pwd, String address, double avg) {
        super(uid, login, uname, phoneno, pwd, address);
        this.avg = avg;
    }

    @Override
    public String toJsonElement() {
        return super.toJsonElement() + ", " + Util.toJsonElement("average", this.avg);
    }
}
