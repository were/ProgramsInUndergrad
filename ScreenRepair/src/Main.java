import javax.swing.*;

import java.awt.*;

public class Main extends JFrame{
	
	public static void main(String args[]) throws InterruptedException {
		JFrame frame = new Main();
		frame.setTitle("T_T");
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1920, 1024);
		frame.setVisible(true);
		MyDrawPanel panel = new MyDrawPanel();
		frame.add(panel);
		while(true) {
			Thread.sleep(40);
//			System.err.println("T_T");
			panel.setVisible(false);
			panel.setVisible(true);
		}
	}
}

class MyDrawPanel extends JPanel {
	final static Color colors[] = {Color.black, Color.blue, Color.cyan, Color.darkGray, Color.gray, Color.green, Color.lightGray, Color.orange, Color.pink, Color.yellow, Color.red, Color.white, Color.MAGENTA};
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(colors[(int) (Math.random() * colors.length)]);
		g.fillRect(0, 0, 1920, 1024);
	}
}
