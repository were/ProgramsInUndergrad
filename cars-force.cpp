#include <cstdio>
#include <cstring>

const int MaxN = 111;

int T, N, cs, cnt[26], ans;
char s[MaxN][MaxN], S[MaxN * MaxN];
bool hsh[MaxN];

void dfs(int x, char *cur) {
	if(x < N) {
		for(int i = 0; i < N; ++i) {
			if(!hsh[i]) {
				hsh[i] = true;
				for(int j = 0; s[i][j]; ++j) {
					cur[j] = s[i][j];
					cur[j + 1] = 0;
				}
				dfs(x + 1, cur + strlen(s[i]));
				hsh[i] = false;
			}
		}
	}
	else {
//puts(S);
		int now = 1;
		for(int i = 0; S[i]; ++i) {
			if(S[i] != S[i + 1]) {
				if(cnt[S[i] - 'a'] != now) {
					return;
				}
				now = 1;
			}
			else {
				++now;
			}
		}
		++ans;
	}
}

int main() {
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		memset(cnt, 0, sizeof cnt);
		ans = 0;
		for(int i = 0; i < N; ++i) {
			scanf("%s", s[i]);
			for(int j = 0; s[i][j]; ++j) {
				++cnt[s[i][j] - 'a'];
			}
		}
		dfs(0, S);
		printf("Case #%d: %d\n", ++cs, ans);
	}
	return 0;
}
