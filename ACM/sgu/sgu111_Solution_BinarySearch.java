import java.util.*;
import java.math.*;
public class Solution{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		BigInteger x = new BigInteger(input.next());
		BigInteger l = BigInteger.ONE, r = x, m, M;
		boolean isVergin = true;
		while(l.compareTo(r) < 0 || isVergin){
			isVergin = false;
			m = l.add(r).divide(BigInteger.valueOf(2));
			if(m.multiply(m).compareTo(x) == 0){
				l = r = m.add(BigInteger.valueOf(1));
				break;
			}
			if(m.multiply(m).compareTo(x) < 0)
				l = m.add(BigInteger.valueOf(1));
			else
				r = m;
		}
		System.out.println(l.subtract(BigInteger.valueOf(1)).toString());
	}
}
