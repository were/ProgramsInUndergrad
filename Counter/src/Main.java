import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Iterator;

public class Main {
	Manager manager = new Manager();
	
	public static void main(String args[]) {
		new Main();
	}
	
}

class Manager {
	int cur;
	Title title = new Title();
	JFrame frame = new JFrame("选票计数器");
	JButton put = new JButton("点我添加候选人（至多五人）");
	JButton gen = new JButton("点我产生结果");
	JButton done = new JButton("点我开始新一轮选举");
	Counter[] counter = new Counter[5];
	
	Manager() {
		for(int i = 0; i < 5; ++i) {
			counter[i] = new Counter();
		}
		title.confirm.addActionListener(new TitleDone());
		put.addActionListener(new ClickPut());
		gen.addActionListener(new ClickGen());
		done.addActionListener(new ClickDone());
		initialLayout();
	}
	
	void unVisionAll() {
		title.setVisible(false);
		put.setVisible(false);
		gen.setVisible(false);
		done.setVisible(false);
		for(int i = 0; i < 5; ++i) {
			counter[i].setVisible(false);
		}
	}
	
	void initialLayout() {
		frame.setSize(512, 768);
		frame.setLayout(new GridLayout(8, 1));
		frame.setVisible(true);
		unVisionAll();
		frame.getContentPane().removeAll();
		
		cur = 0;
		
		title.initialLayout();
		frame.add(title); title.setVisible(true);
		
		put.setFont(new Font("宋体", Font.BOLD, 24));
		
		frame.add(put);
		put.setVisible(false);
		
		for(int i = 0; i < 5; ++i) {
			counter[i].initialLayout();
			frame.add(counter[i]);
			counter[i].setVisible(false);
			counter[i].cnt = 0;
			counter[i].confirmed = false;
		}
		
		gen.setFont(new Font("宋体", Font.BOLD, 24));
		frame.add(gen); gen.setVisible(false);
		
		done.setFont(new Font("宋体", Font.BOLD, 24));
	}
	
	void resLayout() {
		unVisionAll();
		frame.getContentPane().removeAll();
		frame.setSize(512, 386);
		
		frame.setLayout(new GridLayout(3, 1));
		frame.add(title); title.setVisible(true);
		ArrayList<Integer> winners = new ArrayList<Integer>();
		for(int i = 0; i < cur; ++i) {
			if(counter[i].confirmed) {
				if(winners.isEmpty() || counter[winners.get(0)].cnt < counter[i].cnt) {
					winners.clear();
				}
				if(winners.isEmpty() || counter[winners.get(0)].cnt == counter[i].cnt) {
					winners.add(i);
				}
			}
		}
		System.out.println(winners.size());
		String s = "";
		if(winners.isEmpty()) {
			s = "NullPointerException";
		} else {
			if(winners.size() == 1) {
				int winner = winners.get(0); 
				s = "恭喜 " + counter[winner].label.getText().split("：")[1] + " 当选 " + title.area.getText().split("：")[1] + " ！";
			} else {
				for(Iterator<Integer> it = winners.iterator(); it.hasNext();) {
					int idx = it.next();
					System.out.println(idx);
					s = s + counter[idx].label.getText().split("：")[1];
					if(it.hasNext()) {
						 s = s + "、";
					}
				}
				s = s + " " + String.valueOf(winners.size()) + "位同学票数相同";
			}
		}
		CenterLabel res = new CenterLabel(s);
		frame.add(res); res.setVisible(true);
		frame.add(done); done.setVisible(true);
	}
	
	class TitleDone implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			put.setVisible(true);
			gen.setVisible(true);
		}
	}
	
	class ClickPut implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if(cur < 5) {
//				System.out.println("ClickPut" + cur);
				counter[cur++].setVisible(true);
			}
		}
	}
	
	class ClickGen implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			resLayout();
		}
	}
	
	class ClickDone implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			initialLayout();
		}
	}
}

class Counter extends JPanel {
	int cnt = 0;
	JButton inc = new JButton("加一票");
	JButton dec = new JButton("减一票");
	JButton sorry = new JButton("抱歉人家输错了");
	JButton confirm = new JButton("输好了");
	JLabel label = new JLabel();
	JLabel state = new JLabel();
	JTextField field = new JTextField();
	boolean confirmed = false;
	
	class IncListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			state.setText("当前票数：" + String.valueOf(++cnt));
		}
	}
	
	class DecListener implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			if(cnt - 1 >= 0) {
				state.setText("当前票数：" + String.valueOf(--cnt));
			}
		}
	}
	
	class PressEnter implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			checkingLayout();
		}
	}
	
	class ClickSorry implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			initialLayout();
		}
	}
	
	class ClickConfirm implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			votingLayout();
		}
	}
	
	void unVisionAll() {
		inc.setVisible(false);
		dec.setVisible(false);
		confirm.setVisible(false);
		sorry.setVisible(false);
		label.setVisible(false);
		state.setVisible(false);
		field.setVisible(false);
	}
	
	void initialLayout() {
		unVisionAll();
		this.removeAll();
		this.setLayout(new FlowLayout());
		label.setFont(new Font("宋体", Font.PLAIN, 14));
		label.setText("请输入候选人名字：");
		field.setFont(new Font("宋体", Font.PLAIN, 14));
		field.setText("在我这输入候选人名字");
		this.setLayout(new FlowLayout());
		this.add(label); label.setVisible(true);
		this.add(field); field.setVisible(true);
	}
	
	void votingLayout() {
		confirmed = true;
		unVisionAll();
		this.removeAll();
		this.setLayout(new GridLayout(2, 2));
		label.setText("参选同学：" + label.getText());
		label.setFont(new Font("宋体", Font.BOLD, 24));
		state.setText("当前票数：0");
		state.setFont(new Font("宋体", Font.BOLD, 24));
		this.add(label); label.setVisible(true);
		this.add(state); state.setVisible(true);
		this.add(inc); inc.setVisible(true);
		this.add(dec); dec.setVisible(true);
	}
	
	void checkingLayout() {
		unVisionAll();
		this.removeAll();
		this.setLayout(new FlowLayout());
		label.setText(field.getText());
		this.add(label); label.setVisible(true);
		this.add(confirm); confirm.setVisible(true);
		this.add(sorry); sorry.setVisible(true);
	}
	
	Counter() {
		field.addActionListener(new PressEnter());
		sorry.addActionListener(new ClickSorry());
		confirm.addActionListener(new ClickConfirm());
		inc.addActionListener(new IncListener());
		dec.addActionListener(new DecListener());
		initialLayout();
	}
}

class CenterLabel extends JPanel {
	JLabel content = new JLabel();
	CenterLabel(String s) {
		this.add(content);
		content.setText(s);
		content.setFont(new Font("宋体", Font.BOLD, 24));
	}
}

class Title extends JPanel {
	JLabel area = new JLabel();
	JTextField field = new JTextField();
	JButton sorry = new JButton("抱歉人家输错了");
	JButton confirm = new JButton("输好了");
	
	class PressEnter implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			checkingLayout();
		}
	}
	
	class ClickSorry implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			initialLayout();
		}
	}
	
	class ClickConfirm implements ActionListener {
		public void actionPerformed(ActionEvent e) {
			doneLayout();
		}
	}
	
	void unVisionAll() {
		area.setVisible(false);
		field.setVisible(false);
		confirm.setVisible(false);
		sorry.setVisible(false);
	}
	
	void initialLayout() {
		unVisionAll();
		this.removeAll();
		this.setLayout(new FlowLayout());
		area.setText("请输入选举职务：");
		area.setFont(new Font("宋体", Font.PLAIN, 14));
		this.add(area); area.setVisible(true);
		field.setText("在我这输入选举职务");
		field.setFont(new Font("宋体", Font.PLAIN, 14));
		this.add(field); field.setVisible(true);
	}
	
	void checkingLayout() {
		unVisionAll();
		area.setText("即将选举：" + field.getText()); //???
		this.removeAll();
		this.setLayout(new FlowLayout());
		this.add(area); area.setVisible(true);
		this.add(confirm); confirm.setVisible(true);
		this.add(sorry); sorry.setVisible(true);
	}
	
	void doneLayout() {
		unVisionAll();
		area.setText("当前选举职务：" + area.getText().split("：")[1]);
		area.setFont(new Font("宋体", Font.BOLD, 40));
		this.removeAll();
		this.setLayout(new FlowLayout());
		this.add(area); area.setVisible(true);
	}
	
	Title() {
		this.setLayout(new FlowLayout());		
		field.addActionListener(new PressEnter());
		confirm.addActionListener(new ClickConfirm());
		sorry.addActionListener(new ClickSorry());
		initialLayout();
	}
}

