import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class Main {
	Scanner input = new Scanner(System.in);

	final double EPS = 1e-10;

	P isLL(P p1, P p2, P q1, P q2) {
		double d = q2.sub(q1).det(p2.sub(p1));
		if(abs(d) < EPS) {
			return null;
		}
		return p1.add(p2.sub(p1).mul(q2.sub(q1).det(q1.sub(p1)) / d));
	}

	int N;
	boolean oneLine(P p[]) {
		for(int i = 0; i < 4; ++i) {
			for(int j = 0; j < 4; ++j) if(j != i) {
				for(int k = 0; k < 4; ++k) if(k != j && k != i) {
					if(abs(p[i].sub(p[k]).abs() + p[j].sub(p[k]).abs() - p[i].sub(p[j]).abs()) < EPS) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void run() {
		System.out.println("INTERSECTING LINES OUTPUT");
		for(N = input.nextInt(); N != 0; --N) {
			P p[] = new P[4];
			for(int i = 0; i < 4; ++i) {
				double x = input.nextDouble();
				double y = input.nextDouble();
				p[i] = new P(x, y);
			}
			P ans = isLL(p[0], p[1], p[2], p[3]);
			if(ans != null) {
				System.out.printf("POINT %.2f %.2f", ans.x, ans.y);
				System.out.println();
			} else {
				System.out.println(oneLine(p) ? "LINE" : "NONE");
			}
		}
		System.out.println("END OF OUTPUT");
	}

	public static void main(String args[]) {
		new Main().run();
	}
}

class P {
	double x, y;

	P(double x, double y) {
		this.x = x;
		this.y = y;
	}

	P sub(P a) {
		return new P(x - a.x, y - a.y);
	}
	
	P add(P a) {
		return new P(x + a.x, y + a.y);
	}

	P mul(double a) {
		return new P(x * a, y * a);
	}

	double det(P a) {
		return x * a.y - y * a.x;
	}

	double abs() {
		return sqrt(x * x + y * y);
	}
}

