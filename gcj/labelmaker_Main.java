import java.util.*;
import java.math.*;
public class Main{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int T = in.nextInt();
		for(int caseCnt = 1;caseCnt <= T;++ caseCnt){
			String s = in.next(), ans = "";
			BigInteger N = new BigInteger(in.next());
			BigInteger L = BigInteger.valueOf(s.length());
			int ansL = 1;
			while(N.compareTo(L.pow(ansL)) > 0){
				N = N.subtract(L.pow(ansL));
				++ ansL;
			}
			for(int i = 1;i <= ansL;++ i){
				int j = 0;
				while(N.compareTo(L.pow(ansL - i)) > 0){
					N = N.subtract(L.pow(ansL - i));
					++ j;
				}
				ans += s.charAt(j);
			}
			System.out.println("Case #" + caseCnt + ": " + ans);
		}
	}
}
