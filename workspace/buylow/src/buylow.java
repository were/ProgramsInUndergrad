import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;
import java.util.TreeMap;

/*
ID : weng_xo2
PROG : buylow
LANG : JAVA
*/
public class buylow {
	Scanner input = new Scanner(System.in);
	
	int N, a[], f[], nxt[];
	BigInteger cnt[];
	TreeMap<Integer, Integer> pos = new TreeMap<Integer, Integer>();
	
	void run() {
		N = input.nextInt();
		a = new int[N + 1];
		f = new int[N + 1];
		nxt = new int[N + 1];
		cnt = new BigInteger[N + 1];
		for(int i = 0; i <= N; ++i) {
			nxt[i] = N + 1;
		}
		for(int i = 0; i < N; ++i) {
			a[i] = input.nextInt();
			Integer pre = pos.get(a[i]);
			if(pre != null) {
				nxt[pre] = i;
			}
			pos.put(a[i], i);
		}
		a[N] = -1;
		for(int i = 0; i <= N; ++i) {
			f[i] = 1;
			cnt[i] = BigInteger.valueOf(1);
			for(int j = 0; j < i; ++j) {
				if(a[j] > a[i] && nxt[j] > i){
					if(f[i] < f[j] + 1) {
						f[i] = f[j] + 1;
						cnt[i] = BigInteger.ZERO;
					}
					if(f[i] == f[j] + 1) {
						cnt[i] = cnt[i].add(cnt[j]);
					}
				}
			}
//			System.out.println(i + " " + f[i]);
		}
		System.out.println((f[N] - 1) + " " + cnt[N]);
	}
	
	public static void main(String args[]) throws FileNotFoundException {
		System.setIn(new FileInputStream("buylow.in"));
		System.setOut(new PrintStream("buylow.out"));
		new buylow().run();
	}
}
