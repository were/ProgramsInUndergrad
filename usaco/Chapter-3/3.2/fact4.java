/*
ID : weng_xo2
PROG : fact4
LANG : JAVA
*/
import java.io.*;
import java.util.*;
import java.math.*;
public class fact4{
	public static void main(String args[]) throws IOException {
		BufferedReader f = new BufferedReader(new FileReader("fact4.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("fact4.out")));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int N = Integer.parseInt(st.nextToken());
		BigInteger fac = BigInteger.valueOf(1);
		for(int i = 1;i <= N;++ i)
			fac = fac.multiply(BigInteger.valueOf(i));
		String s = fac.toString();
		for(int i = s.length() - 1;i >= 0;-- i){
			if(s.charAt(i) != '0'){
				out.println(s.charAt(i));
				break;
			}
		}
		out.close();
	}
}
