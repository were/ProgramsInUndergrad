#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
const int
	MaxN= 500010,
	inf= ~0u>>3;
int T, N, M, a[MaxN];
int posi, tot;
char s[10];
struct __data{
	int l, r, s, m;
	__data(int l, int r, int s, int m) : l(l), r(r), s(s), m(m) {}
	__data(int x) : l(x), r(x), s(x), m(x) {}
	__data() : l(-inf), r(-inf), s(0), m(-inf) {}
	void show(){
		printf("{l:%d, r:%d, s:%d, m:%d}\n", l, r, s, m);
	}
};
inline int isop(char ch){
	return isupper(ch) || ch=='-';
}
inline __data operator + (const __data&l, const __data&r){
	return __data(
		max(l.l, l.s+r.l),
		max(r.r, r.s+l.r),
		l.s + r.s,
		max(l.r+r.l, max(l.m, r.m))
	);
}
struct __node{
	int ky, sz, same,rev;
	__data data;
	__node*s[2], *p;
	__node() : same(inf) {}
	void clear(){
		ky= sz= rev= 0;s[0]= s[1]= p= 0;
		data= __data();
		same= inf;
	}
	int d(){
		return this == p->s[1];
	}
	__data ans(){
		__data ret= data;
		if(same!=inf)
			ret= same > 0 ? __data(same*sz) : __data(same, same, sz*same, same);
		if(rev)
			swap(ret.r, ret.l);
		return ret;
	}
	void rz(){
		sz= s[0]->sz + 1 + s[1]->sz;
		data= s[0]->ans() + __data(ky) + s[1]->ans();
	}
}*root, nil[MaxN<<3], *size;
void sets(__node*cur, __node*t, int d){
	if((cur->s[d]= t)!=nil)
		t->p= cur;
}
void push(__node*cur){
	if(cur->same!=inf){
		if(cur->s[0]!=nil) cur->s[0]->same= cur->same;
		if(cur->s[1]!=nil) cur->s[1]->same= cur->same;
		cur->ky= cur->same;
		cur->same= inf;
	}
	if(cur->rev){
		swap(cur->s[0], cur->s[1]);
		swap(cur->data.r, cur->data.l);
		if(cur->s[0]!=nil) cur->s[0]->rev^= 1;
		if(cur->s[1]!=nil) cur->s[1]->rev^= 1;
		cur->rev= 0;
	}
	cur->rz();
}
void show(__node*cur){
	if(cur != nil){
		push(cur);
		show(cur->s[0]);
		printf("%d:%d\n", cur->sz, cur->ky, cur->sz);
		cur->ans().show();
		show(cur->s[1]);
	}
}
void rot(__node*t){
	__node*p= t->p;
	int d= t->d();
	sets(p, t->s[!d], d);
	if(p->p != nil)
		sets(p->p, t, p->d());
	else
		(root= t)->p= nil;
	sets(t, p, !d);
	p->rz();
	t->rz();
}
__node*find(int x){
	++ x;
	__node*cur= root;
	push(cur);
	while(x != cur->s[0]->sz + 1)
		if(x < cur->s[0]->sz + 1)
			push(cur= cur->s[0]);
		else{
			x-= cur->s[0]->sz + 1;
			push(cur= cur->s[1]);
		}
	return cur;
}
void spl(__node*t, __node*o){
	o= o->p;
	while(t->p != o)
		if(t->p->p == o)
			rot(t);
		else
			if(t->d() == t->p->d()){
				rot(t->p);
				rot(t);
			}else{
				rot(t);
				rot(t);
			}
}
__node*&range(int f, int t){
	spl(find(f-1), root);
	spl(find(t+1), root->s[1]);
	return root->s[1]->s[0];
}
__node*&build(int f, int t, __node*&cur){
	cur= ++ size;
	cur->ky= a[f+t>>1];
	cur->data= __data(cur->ky);
	cur->sz= 1;
	cur->same= inf;
	(f < f+t>>1) ? build(f, (f+t>>1)-1, cur->s[0])->p= cur : cur->s[0]= nil;
	(f+t>>1 < t) ? build((f+t>>1)+1, t, cur->s[1])->p= cur : cur->s[1]= nil;
	cur->rz();
	return cur;
}
inline void gi(int&x){
	char ch;
	while((ch= getchar(), ch<'0' || ch > '9') && ch!='-');
	if(ch == '-'){
		x= 0;
		while(ch= getchar(), ch>='0' && ch<='9')
			x= x*10 + ch-'0';
		x= -x;
		return;
	}
	x= ch-'0';
	while(ch= getchar(), ch>='0' && ch<='9')
		x= x*10 + ch-'0';
}
void merge(__node*tmp, __node*root){
	push(root);
	if(root->s[1] == nil)
		sets(root, tmp, 1);
	else{
		__node*cur= root->s[1];
		push(cur);
		while(cur->s[0] != nil)
			push(cur= cur->s[0]);
		sets(cur, tmp, 0);
	}
	__node*cur= tmp;
	while(cur->p != nil){
		cur->rz();
		cur= cur->p;
	}
	spl(tmp, root);
}
int main(){
gi(T);
while(T --){
	root= size= nil;
	nil->s[0]= nil->s[1]= nil;
	root->p= nil;
	gi(N); gi(M);
	for(int i= 1;i<= N;++ i)
		gi(a[i+1]);
	a[1]= a[N+2]= -inf;
	build(1, N+2, root)->p= nil;
	while(M --){
		int tail= 0;
		scanf("%s", s);
		if(s[2] == 'S'){
			gi(posi); gi(tot);
			for(int i= 1;i<= tot;++ i)
				gi(a[i]);
			if(tot){
				__node*tmp;
				build(1, tot, tmp)->p= nil;
				spl(find(posi), root);
				merge(tmp, root);
			}
		}
		if(s[2] == 'L'){
			gi(posi); gi(tot);
			if(tot){
				range(posi, posi+tot-1)= nil;
				root->s[1]->rz();
				root->rz();
			}
		}
		if(s[2] == 'K'){
			gi(posi); gi(tot); gi(a[0]);
			if(tot){
				range(posi, posi+tot-1)->same= *a;
				root->s[1]->rz();
				root->rz();
			}
		}
		if(s[2] == 'V'){
			gi(posi); gi(tot);
			if(tot){
				range(posi, posi+tot-1)->rev^= 1;
				root->s[1]->rz();
				root->rz();
			}
		}
		if(s[2] == 'T'){
			gi(posi); gi(tot);
			printf("%d\n", tot ? range(posi, posi+tot-1)->ans().s : 0);
		}
		if(s[2] == 'X'){
			printf("%d\n", root->ans().m);
		}
	}
	for(__node*cur= nil;cur<=size;++ cur)
		cur->clear();

}
	return 0;
}


