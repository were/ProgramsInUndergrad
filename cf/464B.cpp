#include <algorithm>
#include <iostream>

using namespace std;

typedef long long LL;

int a[8][3];

#define sqr(_) ((LL)(_)*(_))

LL dis2(int x, int y) {
	LL res = 0ll;
	for(int i = 0; i < 3; ++i) {
		res += sqr(a[x][i] - a[y][i]);
	}
	return res;
}

#undef sqr

void dfs(int dep) {
	//cout << dep << endl;
	if(dep < 8) {
		if(dep) {
			int tmp[3] = {a[dep][0], a[dep][1], a[dep][2]};
			a[dep][0] = tmp[0]; a[dep][1] = tmp[1]; a[dep][2] = tmp[2]; dfs(dep + 1);
			a[dep][0] = tmp[0]; a[dep][1] = tmp[2]; a[dep][2] = tmp[1]; dfs(dep + 1);
			a[dep][0] = tmp[1]; a[dep][1] = tmp[0]; a[dep][2] = tmp[2]; dfs(dep + 1);
			a[dep][0] = tmp[1]; a[dep][1] = tmp[2]; a[dep][2] = tmp[0]; dfs(dep + 1);
			a[dep][0] = tmp[2]; a[dep][1] = tmp[0]; a[dep][2] = tmp[1]; dfs(dep + 1);
			a[dep][0] = tmp[2]; a[dep][1] = tmp[1]; a[dep][2] = tmp[0]; dfs(dep + 1);
			a[dep][0] = tmp[0]; a[dep][1] = tmp[1]; a[dep][2] = tmp[2];
		} else {
			dfs(dep + 1);
		}
	} else {
		LL dis[64], x, y, z;
		int tot = 0;
		for(int i = 0; i < 8; ++i) {
			for(int j = i + 1; j < 8; ++j) {
				dis[tot++] = dis2(i, j);
			}
		}
		sort(dis, dis + tot);
		int cur = 0, l;

		x = dis[cur];
		if(x == 0) {
			return;
		}
		for(l = cur; cur < tot && dis[cur] == dis[l]; ++cur);
		if(cur - l != 12) {
			return;
		}

		y = dis[cur];
		if(x + x != y) {
			return;
		}
		for(l = cur; cur < tot && dis[cur] == dis[l]; ++cur);
		if(cur - l != 12) {
			return;
		}

		z = dis[cur];
		if(x + y != z) {
			return;
		}
		for(l = cur; cur < tot && dis[cur] == dis[l]; ++cur);
		if(cur - l != 4) {
			return;
		}

		cout << "YES\n";
		for(int i = 0; i < 8; ++i) {
			cout << a[i][0] << " " << a[i][1] << " " << a[i][2] << endl;
		}
		
		exit(0);
	}
}

int main() {
	for(int i = 0; i < 8; ++i) {
		for(int j = 0; j < 3; ++j) {
			cin >> a[i][j];
		}
	}
	dfs(0);
	cout << "NO\n";
	return 0;
}
