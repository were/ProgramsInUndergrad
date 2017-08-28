#include <iostream>

using std::cin;
using std::cout;

int T, cs, a[5][5], b[5][5], x, y;

void work(){
	int ans = -1;
	for(int i = 1; i <= 4; ++i)
		for(int j = 1; j <= 4; ++j)
			if(a[x][i] == b[y][j]){
				if(ans == -1){
					ans = a[x][i];
				}
				else{
					cout << "Bad magician!\n";
					return;
				}
			}
	if(ans == -1){
		cout << "Volunteer cheated!\n";
	}
	else{
		cout << ans << "\n";
	}
}

int main(){
	cin >> T;
	while(T--){
		cin >> x;
		for(int i = 1; i <= 4; ++i)
			for(int j = 1; j <= 4; ++j)
				cin >> a[i][j];
		cin >> y;
		for(int i = 1; i <= 4; ++i)
			for(int j = 1; j <= 4; ++j)
				cin >> b[i][j];
		cout << "Case #" << ++cs << ": ";
		work();
	}
}
