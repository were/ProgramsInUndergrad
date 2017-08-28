import java.util.*;
public class Solution{
	static public void main(String[] args){
		Scanner in = new Scanner(System.in);
		int N = in.nextInt();
		if(N != 2){
			System.out.print(N);
			for(int i = 0;i < N;++i)
				for(int j = 0;j < N;++j)
					if(i + j > N)
						System.out.print(" " + (i * N + j + 1));
			System.out.println("");
		}
		for(int dis = N, step = ((N - 1) / 2 + 1) * 2 + 1;dis > 0;step += 2, --dis){
			System.out.print(step);
			for(int i = 0;i < N;++i)
				for(int j = 0;j < N;++j)
					if(i + j == dis)
						System.out.print(" " + (i * N + j + 1));
			System.out.println("");
		}
	}
}
