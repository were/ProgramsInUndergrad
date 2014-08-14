import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;


public class Main {

	
	int[] split(int x) {
		int ret[] = new int[4];
		for(int i = 3; i >= 0; --i) {
			ret[i] = x & ((1 << 8) - 1);
			x >>= 8;
		}
		return ret;
	}
	
	int merge(int []a) {
		int ret = 0;
		for(int i = 0; i < a.length; ++i) {
			ret = ret << 8 | a[i];
		}
		return ret;
	}
	
	void run() throws IOException {
		BufferedImage input = ImageIO.read(new File("input.jpg"));
		for(int i = 0; i < input.getWidth(); ++i) {
			for(int j = 0; j < input.getHeight(); ++j) {
				//System.out.println(i + " " + j);
				int []a = split(input.getRGB(i, j));
				int t = a[1] + a[2] + a[3];
				System.out.println(a[0]);
				a[1] = a[2] = a[3] = t / 3;
				input.setRGB(i, j, merge(a));
			}
		}
		ImageIO.write(input, "jpg", new File("output.jpg"));
	}
	
	public static void main(String []args) throws IOException {
		new Main().run();
	}
}
