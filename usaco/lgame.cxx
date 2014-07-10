/*
ID : weng_xo2
PROG : lgame
LANG : C++11
Programmed by wereFluke
C++0x stardard head file
*/
#include <algorithm>
#include <bitset>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#define X first
#define Y second

using std::sort;
using std::max;
using std::min;
using std::swap;
using std::lower_bound;
using std::upper_bound;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::tuple;
using std::make_tuple;
using std::vector;
using std::map;
using std::set;
using std::priority_queue;
using std::string;
using std::pair;
using std::make_pair;
using std::less;
using std::greater;
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::clog;
using std::ifstream;
using std::ofstream;
using std::queue;
using std::stack;
using std::deque;
using std::list;
using std::bitset;

using ll = long long;
using vi = vector<int>;
using mii = map<int, int>;
using pii = pair<int, int>;

FILE *input = fopen("lgame.in", "r"),
	*output = fopen("lgame.out", "w"),
	*dict = fopen("lgame.dict", "r");

const char
	keyboard[] = "qwertyuiopasdfghjklzxcvbnm",
	score[] = "76122541352146557637746525";


char s[10], tmp[10], words[5000][10], maxScore, buffer[5000][10], *forOutput[5000];
int N, delta[26];
vector<char*> ans;
vector<pair<char*, char*> > res;

struct Data {
	int cnt[26], score;
	Data() {
		memset(cnt, 0, sizeof cnt);
		score = 0;
	}
	Data(char *s) {
		memset(cnt, 0, sizeof cnt);
		score = 0;
		for(int i = 0; s[i]; ++i) {
			++cnt[s[i] - 'a'];
			score += delta[s[i] - 'a'];
		}
	}
}a, weight[5000];

bool operator<= (const Data &a, const Data &b) {
	for(int i = 0; i < 26; ++i) {
		if(a.cnt[i] > b.cnt[i]) {
			return false;
		}
	}
	return true;
}

bool cmp(char *a, char *b) {
	return strcmp(a, b) < 0;
}

Data operator+ (const Data &a, const Data &b) {
	Data ret;
	for(int i = 0; i < 26; ++i) {
		ret.cnt[i] = a.cnt[i] + b.cnt[i];
	}
	ret.score = a.score + b.score;
	return ret;
}

int main() {
	for(int i = 0; keyboard[i]; ++i) {
		delta[keyboard[i] - 'a'] = score[i] - '0';
	}
	fscanf(input, "%s", s);
	a = Data(s);
	while(fscanf(dict, "%s", tmp), strcmp(tmp, ".")) {
		if(Data(tmp) <= a) {
			strcpy(words[N], tmp);
			weight[N] = Data(tmp);
			if(weight[N].score > maxScore) {
				maxScore = weight[N].score;
				ans.clear();
			}
			if(weight[N].score == maxScore) {
				ans.push_back(words[N]);
			}
			++N;
		}
	}
	//for(int i = 0; i < N; ++i) {
	//	puts(words[i]);
	//}
	for(int i = 0; i < N; ++i) {
		for(int j = i; j < N; ++j) if(weight[i] + weight[j] <= a) {
			if(weight[i].score + weight[j].score > maxScore) {
				ans.clear();
				res.clear();
				maxScore = weight[i].score + weight[j].score;
			}
			if(weight[i].score + weight[j].score == maxScore) {
				res.push_back(make_pair(words[i], words[j]));
			}
		}
	}
	fprintf(output, "%d\n", maxScore);
	for(unsigned i = 0; i < ans.size(); ++i) {
		sprintf(forOutput[i] = buffer[i], "%s\n", ans[i]);
	}
	for(unsigned i = 0; i < res.size(); ++i) {
		sprintf(forOutput[i + ans.size()] = buffer[i + ans.size()], "%s %s\n", res[i].X, res[i].Y);
	}
	sort(forOutput, forOutput + ans.size() + res.size(), cmp);
	for(unsigned i = 0; i < ans.size() + res.size(); ++i) {
		fputs(forOutput[i], output);
	}
	return 0;
}

