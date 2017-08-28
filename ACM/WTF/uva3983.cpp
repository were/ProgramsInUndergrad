#include <cstdio>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

crope buffer[55555];
int T, cur, d;
char s[1111111];

int main() {
	scanf("%d", &T);
	while(T--) {
		int op;
		scanf("%d", &op);
		if(op == 1) {
			int pos;
			scanf("%d%s", &pos, s);
			pos -= d;
			buffer[cur + 1] = buffer[cur];
			buffer[++cur].insert(pos, s);
		}
		if(op == 2) {
			int pos, len;
			scanf("%d%d", &pos, &len);
			pos -= d + 1;
			len -= d;
			buffer[cur + 1] = buffer[cur];
			buffer[++cur].erase(pos, len);
		}
		if(op == 3) {
			int v, pos, len;
			scanf("%d%d%d", &v, &pos, &len);
			v -= d;
			pos -= d + 1;
			len -= d;
			buffer[v].copy(pos, len, s);
			s[len] = 0;
			puts(s);
			for(int i = 0; s[i]; ++i) {
				if(s[i] == 'c') {
					++d;
				}
			}
		}
	}
	return 0;
}

