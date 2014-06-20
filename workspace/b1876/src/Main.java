import java.math.BigInteger;
import java.util.Scanner;


public class Main {
	Scanner in = new Scanner(System.in);
	
	void run() {
		BigInteger a = in.nextBigInteger();
		BigInteger b = in.nextBigInteger();
		while(b.compareTo(BigInteger.ZERO) != 0) {
			BigInteger c = a.mod(b);
			a = b;
			b = c;
		}
		System.out.println(a);
	}
	
	public static void main(String []args) {
		new Main().run();
	}
}
