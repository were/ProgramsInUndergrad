import java.util.*;
import java.math.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int a = in.nextInt(), b = in.nextInt();
		BigInteger A = BigInteger.valueOf(a), B = BigInteger.valueOf(b);
		A = A.pow(b);
		B = B.pow(a);
		System.out.println(A.subtract(B));
	}
}
