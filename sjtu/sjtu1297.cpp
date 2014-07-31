#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

#define X first
#define Y second
typedef pair<int, int> PII;

queue< vector<PII> > q;
map<vector<PII>, int> dis;

int N, M, len;
char s[20][20];
vector<PII> tmp, data;

bool cmp(PII a, PII b) {
	return s[a.X][a.Y] < s[b.X][b.Y];
}

bool inRange(int x, int y) {
	if(x < 1 || x > N || y < 1 || y > M) {
		return false;
	}
	if(s[x][y] == '#') {
		return false;
	}
	PII pos(x, y);
	for(size_t i = 0; i < tmp.size(); ++i) {
		if(pos == tmp[i]) {
			return false;
		}
	}
	data.clear();
	data.push_back(pos);
	//data.insert(data.end(), tmp.begin(), tmp.end());
	for(int i = 0; i < (int) tmp.size(); ++i) {
		data.push_back(tmp[i]);
	}
	return dis[data] == 0;
}

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i) {
		scanf("%s", s[i] + 1);
		for(int j = 1; j <= M; ++j) {
			if(isdigit(s[i][j])) {
				tmp.push_back(PII(i, j));
			}
		}
	}
	sort(tmp.begin(), tmp.end(), cmp);
	q.push(tmp);
	dis[tmp] = 1;
	while(!q.empty()) {
		tmp = q.front();
//for(size_t i = 0; i < tmp.size(); ++i) printf("(%d, %d) ", tmp[i].X, tmp[i].Y); puts("");
		int cur = dis[tmp];
		q.pop();
		tmp.pop_back();
		for(int i = -1; i <= 1; ++i) {
			for(int j = -1; j <= 1; ++j) {
				int x = tmp.begin()->X + i, y = tmp.begin()->Y + j;
				if(abs(i) + abs(j) == 1 && inRange(x, y)) {
					q.push(data);
					dis[data] = cur + 1;
					if(s[data.begin()->X][data.begin()->Y] == '@') {
						printf("%d\n", dis[data] - 1);
						return 0;
					}
				}
			}
		}
	}
	puts("-1");
	return 0;
}
