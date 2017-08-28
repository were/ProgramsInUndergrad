import java.util.*;
import java.math.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		BigInteger X = new BigInteger(in.next()), ans = BigInteger.ONE, preAns = BigInteger.ZERO;
		while(ans.compareTo(preAns) != 0){
			preAns = ans;
			ans = ans.subtract(ans.pow(2).subtract(X).divide(ans).divide(new BigInteger("2")));
		}
		if(ans.pow(2).compareTo(X) > 0)
			ans = ans.subtract(BigInteger.ONE);
		System.out.println(ans);
	}
}
