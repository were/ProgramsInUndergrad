import java.util.Scanner;


public class Solution {
	Scanner input = new Scanner(System.in);
	
	void run() {
		Long N = input.nextLong();
		Long x = new Long(0);
		for(; (x + (long)1) * ((long)1 << (x + (long)1)) < N + (long)1; ++x);
		System.out.println(x);
	}
	
	public static void main(String []args) {
		new Main().run();
	}
}
