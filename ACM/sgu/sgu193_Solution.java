import java.util.*;
import java.math.*;
public class Solution {
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);

		BigInteger zero = new BigInteger("0");
		BigInteger one  = new BigInteger("1");
		BigInteger two  = new BigInteger("2");
		BigInteger three= new BigInteger("3");
		BigInteger four = new BigInteger("4");

		BigInteger N = in.nextBigInteger();
		BigInteger n = N.subtract(three).divide(four).multiply(two).add(one);

		if(N.subtract(three).mod(four).compareTo(two) == 0){
			n = n.add(one);
		}

		System.out.println(n);
	}
}
