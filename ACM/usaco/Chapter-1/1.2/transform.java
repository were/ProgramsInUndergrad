/*
ID : weng_xo2
LANG : JAVA
PROG : transform
*/

import static java.lang.Math.*;
import static java.util.Arrays.*;

import java.io.*;
import java.util.*;
import java.math.*;

public class transform {
	Scanner input = new Scanner(System.in);

	int N;
	char origin[][], destin[][];
	String s;

	char[][] rotate(char grid[][]) {
		char ret[][] = new char[N][N];
		for(int i = 0, y = N - 1; i < N; ++i, --y) {
			for(int j = 0, x = 0; j < N; ++j, ++x) {
				ret[x][y] = grid[i][j];
			}
		}
		return ret;
	}

	char[][] mirror(char grid[][]) {
		char ret[][] = new char[N][N];
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				ret[i][j] = grid[i][N - 1 - j];
			}
		}
		return ret;
	}

	boolean equal(char a[][], char b[][]) {
		for(int i = 0; i < N; ++i) {
			for(int j = 0; j < N; ++j) {
				if(a[i][j] != b[i][j]) {
					return false;
				}
			}
		}
		return true;
	}

	void run() {
		N = input.nextInt();
		origin = new char[N][N];
		for(int i = 0; i < N; ++i) {
			s = input.next();
			for(int j = 0; j < N; ++j) {
				origin[i][j] = s.charAt(j);
			}
		}
		destin = new char[N][N];
		for(int i = 0; i < N; ++i) {
			s = input.next();
			for(int j = 0; j < N; ++j) {
				destin[i][j] = s.charAt(j);
			}
		}
		char tmp[][] = origin;
		for(int i = 1; i <= 3; ++i) {
			tmp = rotate(tmp);
			if(equal(tmp, destin)) {
				System.out.println(i);
				return;
			}
		}
		if(equal(mirror(origin), destin)) {
			System.out.println(4);
			return;
		}
		tmp = origin;
		for(int i = 1; i <= 3; ++i) {
			tmp = rotate(tmp);
			if(equal(mirror(tmp), destin)) {
				System.out.println(5);
				return;
			}
		}
		if(equal(origin, destin)) {
			System.out.println(6);
			return;
		}
		System.out.println(7);
	}

	public static void main(String args[]) {
		try {
			System.setIn(new FileInputStream("transform.in"));
			System.setOut(new PrintStream("transform.out"));
		}
		catch (Throwable e) {
			System.err.println("FileNotExist!");
			return;
		}
		new transform().run();
	}
}

