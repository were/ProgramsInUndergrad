import java.util.*;
import java.math.*;
public class Solution{
	public static void main(String[] args){
		Scanner in = new Scanner(System.in);
		int K = in.nextInt();
		for(int k = 0;k < K;++k){
			int N = in.nextInt(), Res = 0;
			BigInteger sum = BigInteger.valueOf(0), tmp = BigInteger.valueOf(1);
			for(int i = 0;i < N;++i){
				tmp = tmp.multiply(BigInteger.valueOf(in.nextInt()));
				sum = sum.add(tmp);
			}
			String res = sum.toString();
			for(int i = 0;i < res.length();++i){
				Res += (int)res.charAt(i) - (int)'0';
			}
			while(Res >= 10){
				int tmpRes = Res;
				Res = 0;
				while(tmpRes != 0){
					Res += tmpRes % 10;
					tmpRes /= 10;
				}
			}
			System.out.println(Res);
		}
	}
}
