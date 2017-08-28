/*
LANG : JAVA
PROG : lamps
ID : weng_xo2
*/
import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class lamps {
	Scanner input = new Scanner(System.in);

	int N, C, req[], lamp[];
	
	ArrayList<String> ans = new ArrayList<String>();

	int cnt(int x) {
		int ret = 0;
		while(x != 0) {
			++ret;
			x -= x & -x;
		}
		return ret;
	}

	void run() {
		N = input.nextInt();
		C = input.nextInt();
		req = new int[N + 1];
		lamp = new int[N + 1];
		Arrays.fill(req, -1);
		for(int x = input.nextInt(); x != -1; x = input.nextInt()) {
			req[x] = 1;
		}
		for(int x = input.nextInt(); x != -1; x = input.nextInt()) {
			if(req[x] == -1) {
				req[x] = 0;
			} else {
				if(req[x] == 1) {
					System.out.println("IMPOSSIBLE");
					System.exit(0);
				}
			}
		}
		for(int mask = 0; mask < (1 << 4); ++mask) {
			int ones = cnt(mask);
			if(ones > C || (C - ones) % 2 == 1) {
				continue;
			}
			boolean flag = true;
			for(int i = 1; i <= N; ++i) {
				lamp[i] = 1;
				lamp[i] ^= (mask & 1);
				if(i % 2 == 1) {
					lamp[i] ^= (mask >> 1 & 1);
				} else {
					lamp[i] ^= (mask >> 2 & 1);
				}
				if(i % 3 == 1) {
					lamp[i] ^= (mask >> 3 & 1);
				}
				if(req[i] != -1 && lamp[i] != req[i]) {
					flag = false;
					break;
				}
			}
			if(flag) {
				String s = "";
				for(int i = 1; i <= N; ++i) {
					s = s + Integer.toString(lamp[i]);
				}
				ans.add(s);
			}
		}
		Collections.sort(ans);
		if(ans.size() != 0) {
			for(int i = 0; i < ans.size(); ++i) {
				System.out.println(ans.get(i));
			}
		} else {
			System.out.println("IMPOSSIBLE");
		}
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("lamps.in"));
			System.setOut(new PrintStream("lamps.out"));
		}
		catch (Throwable T_T) {
		}
		new lamps().run();
	}
}

