#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MaxN = 500010, inf= ~0u>> 2;
char inputBuf[25555555], *hd= inputBuf, outputBuf[25555555], *tl= outputBuf;
struct __data{
	int l, r, s, m;
	__data(int l, int r, int s, int m) : l(l), r(r), s(s), m(m) {}
	__data(int x) : l(x), r(x), s(x), m(x) {}
	__data() : l(-inf), r(-inf), s(0), m(-inf) {}
	void show(){
		printf("l:%d r:%d s:%d m:%d\n", l, r, s, m);
	}
};
__data operator + (const __data&l, const __data&r){
	return __data(
		max(l.l, l.s + r.l),
		max(r.r, r.s + l.r),
		l.s + r.s,
		max(l.r + r.l, max(l.m, r.m))
	);
}
struct __node{
	__data dt;
	int v, sz, sm, rev, pri;
	__node*l, *r;
	__data ans(){
		static __data ret;
		ret= dt;
		if(sm != -inf)
			ret= sm > 0 ? __data(sm*sz) : __data(sm, sm, sm*sz, sm);
		if(rev)
			swap(ret.l, ret.r);
		return ret;
	}
	void push(){
		dt= ans();
		if(rev){
			if(l->sz) l->rev^= 1;
			if(r->sz) r->rev^= 1;
			rev= 0;
			swap(l, r);
		}
		if(sm != -inf){
			if(l->sz) l->sm= sm;
			if(r->sz) r->sm= sm;
			v= sm;
			sm= -inf;
		}
	}
	__node*rz(){
		dt= (l->sz ? l->ans() : __data()) + __data(v) + (r->sz ? r->ans() : 

__data());
		sz= l->sz + 1 + r->sz;
		return this;
	}
	void show(){
		printf("sz : %d\n", sz);
		printf("v : %d\n", v);
		ans().show();
		puts("");
	}
}nil[MaxN], *buf[MaxN], **top= buf, *root;
int a[MaxN], T, N, M, x, y, c;
char op[30];
__node*newNode(int v){
	(*top)->v= v;
	(*top)->sz= 1;
	(*top)->sm= -inf;
	(*top)->dt= __data(v);
	(*top)->rev= 0;
	(*top)->pri= rand();
	(*top)->l= (*top)->r= nil;
	return *top --;
}
void collect(__node*&cur){
	if(cur == nil)
		return;
	collect(cur->l);
	collect(cur->r);
	*(++ top)= cur;
//	cur= nil;
}
__node*merge(__node*l, __node*r){
//	printf("merging... %x %x\n", l, r);
//	printf("%d\n", l==nil || r==nil);
	l->push();
	r->push();
	if(l==nil || r==nil){
//		puts("return...");
		return l - nil + r;
	}
	if(l->pri > r->pri){
		l->r= merge(l->r, r);
		return l->rz();
	}else{
		r->l= merge(l, r->l);
		return r->rz();
	}
}
void dfs(__node*cur){
	if(cur != nil){
		dfs(cur->l);
		cur->show();
		dfs(cur->r);
	}
}
__node*build(int f,int t){
	return f==t ? newNode(a[f]) : merge(build(f, f+t>>1), build((f+t>>1)+1, t));
//	__node*ret= f==t ? newNode(a[f]) : merge(build(f, f+t>>1), build((f+t>>1)+1, t));
//	printf("[%d,%d]\n", f, t);
//	dfs(ret);
//	return ret;
}
__node*cut(__node*&cur, int k){
	if(cur == nil)
		return nil;
	cur->push();
	__node*ret;
	if(k > cur->l->sz + 1){
		ret= cur;
		__node*tmp= cut(cur->r, k - cur->l->sz - 1);
		cur= cur->r;
		ret->r= tmp;
		ret->rz();
	}else{
		ret= cut(cur->l, k);
		cur->rz();
	}
	return ret;
}
int gi(){
	while(!isdigit(*hd) && *hd!='-')
		++ hd;
	if(*hd == '-'){
		++ hd;
		return -gi();
	}
	int ret= *hd ++ - '0';
	while(isdigit(*hd))
		ret= ret*10 + *hd ++ - '0';
	return ret;
}
void gs(char *s){
	while(!isupper(*hd))
		++ hd;
	while(isupper(*hd) || *hd == '-')
		*s ++= *hd ++;
	*s= 0;
}
void pi(int x){
	if(x < 0){
		*tl ++ = '-';
		pi(-x);
	}else{
		if(x >= 10)
			pi(x / 10);
		*tl ++= '0' + (x % 10);
	}
}
int main(){
//	freopen("input.txt", "r", stdin);
//	printf("nil is %x\n", nil);
//	srand(time(0));
	fread(hd, 1, 25000000, stdin);
//	puts(hd);
	nil->l= nil->r= nil;
	for(int i= 1;i< MaxN;++ i)
		*(++ top)= nil + i;
//	scanf("%d", &T);
	T= gi();
//	int T= 1;
	while(T --){
//		scanf("%d%d", &N, &M);
		N= gi(); M= gi();
//		printf("%d %d\n", N, M);
		for(int i= 1;i<= N;++ i)
			a[i]= gi();
//			scanf("%d", a+i);
		root= build(1, N);
//		puts(hd);
/*
		puts("build done...");
		__node*tmp= cut(root, 4);
		dfs(root);
		puts("------------------------------");
		dfs(tmp);
*/
//		printf("%d\n", M)
		while(M --){
//			scanf("%s", op);
//			printf("%d:\n", M);
//			puts(op);
			gs(op);
//			puts(op);
			__node*l, *m;
			if(op[2] == 'K'){
//				scanf("%d%d%d", &x, &y, &c); ++ y;
				x= gi(); y= gi(); c= gi(); ++ y;
				l= cut(root, x);
				m= cut(root, y);
				m->sm= c;
				l= merge(l, m);
				root= merge(l, root);
			}
			if(op[2] == 'S'){
				x= gi() + 1; y= gi();
//				scanf("%d%d", &x, &y); ++ x;
				for(int i= 1;i<= y;++ i)
					a[i]= gi();
//					scanf("%d", a+i);
				m= build(1, y);
				l= cut(root, x);
				l= merge(l, m);
				root= merge(l, root);
//				puts("insert done..."); dfs(root);
			}
			if(op[2] == 'L'){
//				scanf("%d%d", &x, &y); ++ y;
				x= gi(); y= gi() + 1;
				l= cut(root, x);
				m= cut(root, y);
				collect(m);
				root= merge(l, root);
//				puts("delete done..."); dfs(root);
			}
			if(op[2] == 'V'){
//				scanf("%d%d", &x, &y); ++ y;
				x= gi(); y= gi() + 1;
				l= cut(root, x);
				m= cut(root, y);
				m->rev^= 1;
				l= merge(l, m);
				root= merge(l, root);
			}
			if(op[2] == 'T'){
//				puts(op);
//				scanf("%d%d", &x, &y); ++ y;
				x= gi(); y= gi()+1;
				l= cut(root, x);
//				puts("root"); dfs(root);
				m= cut(root, y);
//				puts("L"); dfs(l);
//				puts("M"); dfs(m);
//				puts("R"); dfs(root);
				pi(m->ans().s); *tl ++= '\n';
//				printf("%d\n", m->ans().s);
				l= merge(l, m);
				root= merge(l, root);
			}
			if(op[2] == 'X'){
//				puts(op);
//				printf("%d\n", root->ans().m);
				pi(root->ans().m); *tl ++= '\n';
			}
		}
		collect(root); root= nil;
	}
	fwrite(outputBuf, tl-outputBuf, 1, stdout);
	return 0;
}


