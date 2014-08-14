import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.PrintStream;

import javax.imageio.ImageIO;

public class Main {
	
	final int Width = 500, Height = 500;
	
	int mergeColor(int r, int g, int b) {
		int ret = 255;
		ret <<= 8;
		ret |= r;
		ret <<= 8;
		ret |= g;
		ret <<= 8;
		ret |= b;
		return ret;
	}
	
	void run() throws IOException {
		BufferedImage image = new BufferedImage(Width, Height, BufferedImage.TYPE_INT_RGB);
//		Vec3 O = new Vec3(Width / 4 * 3, Height / 4 * 3, -1/*-(Width + Height) / 2*/);
		Vec3 O = new Vec3(Width / 10, -10, Height / 2);
		Sphere ball = new Sphere(new Vec3(500, 100, 100), 100);
		Plane grid = new Plane(0, 0, 1);
		for(int i = 0; i < Width; ++i) {
			for(int j = 0; j < Height; ++j) {
				Ray ray = new Ray(O, new Vec3(i - O.x + 500, -O.y, j - O.z));
				double t1 = ray.shoot(grid);
				double t2 = ray.shoot(ball);
//				System.out.println(t1 + " " + t2);
				boolean onBall;
				int color = 0;
				double t;
				if(t1 > 0 && t2 < 0) {
					t = t1;
					onBall = false;
				}
				else {
					if(t1 < 0 && t2 > 0) {
						t = t2;
						onBall = true;
					}
					else {
						if(t1 < t2) {
							t = t1;
							onBall = false;
						}
						else {
							t = t2;
							onBall = true;
						}
					}
				}
//				System.out.println(t + (onBall ? "Ball" : "Grid"));
				if(t > 0) {
					Vec3 terminal = ray.getTerminal(t);
					Ray newRay = new Ray(terminal, null);
					Vec3 nomal = onBall ? newRay.o.getVec(ball.o) : new Vec3(0, 0, 1);
					t = 2 * (nomal.inner(ray.dir)) / (nomal.length() * nomal.length());
					newRay.dir = nomal.multiply(t).getVec(ray.dir);
//					System.out.println(newRay.shoot(ball));
					System.out.println(terminal.x + " " + terminal.y);
					if((!onBall && newRay.shoot(ball) < 0) || (onBall && newRay.shoot(grid) < 0)) {
						if(!onBall) {
							long x = Math.round(terminal.x / 200);
							long y = Math.round(terminal.y);
							if((x + y) % 2 == 1) {
								color = mergeColor(0, 0, 0);
							}
							else {
								color = mergeColor(255, 255, 255);
							}
						}
						else {
							color = mergeColor(15, 200, 15);
						}
					}
					else {
						color = mergeColor(200, 200, 200);
					}
				}
				else {
					color = mergeColor(127, 127, 127);
				}
				System.out.println((Width - i - 1) + " " + (Height - j - 1));
				image.setRGB(Width - i - 1, Height - j - 1, color);
			}
		}
		ImageIO.write(image, "jpg", new File("output.jpg"));
	}
	
	public static void main(String[] args) throws IOException {
		System.setOut(new PrintStream("generating.log"));
		new Main().run();
	}
}

class Plane {
	double A, B, C;
	Plane(double A, double B, double C) {
		this.A = A;
		this.B = B;
		this.C = C;
	}
}

class Vec3 {
	double x, y, z;
	
	Vec3(double x, double y, double z) {
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	Vec3 getVec(Vec3 b) {
		return new Vec3(b.x - this.x, b.y - this.y, b.z - this.z);
	}
	
	double inner(Vec3 b) {
		return this.x * b.x + this.y * b.y + this.z * b.z;
	}
	
	double length() {
		return Math.sqrt(this.inner(this));
	}
	
	Vec3 multiply(double t) {
		return new Vec3(this.x * t, this.y * t, this.z * t);
	}
}

class Ray {
	Vec3 o, dir;
	
	Ray(Vec3 o, Vec3 dir) {
		this.o = o;
		this.dir = dir;
	}
	
	double shoot(Plane x) {
		double b = x.A * o.x + x.B * o.y + x.C * o.z;
		double a = x.A * dir.x + x.B * dir.y + x.C * dir.z;
		if(a != 0) {
			return -b / a;
		}
		return -1;
	}
	
	double shoot(Sphere x) {
		Vec3 tmp = o.getVec(x.o);
		double a = this.dir.inner(this.dir);
		double b = this.dir.inner(tmp) * 2.;
		double c = tmp.inner(tmp) - x.r * x.r;
		double delta  = b * b - 4 * a * c;
		if(delta < 0) {
			return -1;
		}
		delta = Math.sqrt(delta);
		double ret = 1e9;
		ret = Math.min(ret, (-b + delta) / 2 / a > 0 ? (-b + delta) / 2 / a : 1e9);
		ret = Math.min(ret, (-b - delta) / 2 / a > 0 ? (-b - delta) / 2 / a : 1e9);
//		Vec3 point = getTerminal(ret);
//		System.out.println(x.r + " ?=? " + point.getVec(x.o).length());
		return ret == 1e9 ? -1 : ret;
	}
	
	Vec3 getTerminal(double t) {
		return new Vec3(o.x + t * dir.x, o.y + t * dir.y, o.z + t * dir.z);
	}
}

class Sphere {
	Vec3 o;
	double r;
	Sphere(Vec3 o, double r) {
		this.o = o;
		this.r = r;
	}
}