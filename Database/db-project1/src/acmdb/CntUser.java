package acmdb;

/**
 * Created by were on 16/6/11.
 */
public class CntUser extends User {
    int cnt;
    public CntUser(int uid, String login, String uname, String phoneno, String pwd, String address, int cnt) {
        super(uid, login, uname, phoneno, pwd, address);
        this.cnt = cnt;
    }

    @Override
    public String toJsonElement() {
        return super.toJsonElement() + "," + Util.toJsonElement("cnt", this.cnt);
    }
}
