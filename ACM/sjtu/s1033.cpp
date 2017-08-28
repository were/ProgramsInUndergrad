#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <stack>

using std :: stack;

typedef long long ll;

char express[111], *cur = express;
stack<char> op;
stack<ll> num;

ll popNum(){
	if(num.empty()){
		puts("Error");
		exit(0);
	}
	ll ret = num.top();
	num.pop();
	return ret;
}

void popOp(){
	if(op.empty()){
		puts("Error");
		exit(0);
	}
	if(op.top() == '+'){
		ll b = popNum();
		ll a = popNum();
		num.push(a + b);
//		printf("%lld + %lld = %lld\n", a, b, a + b);
	}
	if(op.top() == '-'){
		ll b = popNum();
		ll a = popNum();
		num.push(a - b);
//		printf("%lld - %lld = %lld\n", a, b, a - b);
	}
	if(op.top() == '*'){
		ll b = popNum();
		ll a = popNum();
		num.push(a * b);
//		printf("%lld * %lld = %lld\n", a, b, a * b);
	}
	if(op.top() == '/'){
		ll b = popNum();
		ll a = popNum();
		if(b){
			num.push(a / b);
//			printf("%lld / %lld = %lld\n", a, b, a / b);
		}else{
			puts("Error");
			exit(0);
		}
	}
	if(op.top() == '^'){
		ll b = popNum();
		ll a = popNum();
		if(a){
			ll ret = 1ll;
//			printf("%lld ^ %lld = ", a, b);
			if(a != 1ll && a != -1ll){
				while(b--){
					ret *= a;
				}
			}else{
				if(a == -1)
					ret = b % 2 ? -1 : 1;
			}
			num.push(ret);
//			printf("%lld\n", ret);
		}else
			num.push(0);
	}
	if(op.top() == '%'){
		ll a = popNum();
//		printf("%lld\n", -a);
		num.push(-a);
	}
	op.pop();
}

int main(){
//	freopen("input", "r", stdin);
	for(gets(express);*cur;++cur){
		if(isdigit(*cur)){
			int x = 0;
			while(isdigit(*cur))
				x = x * 10 + *cur++ - '0';
			--cur;
//			printf("%d\n", x);
			num.push(x);
		}
		if(*cur == '('){
			op.push('(');
		}
		if(*cur == ')'){
			while(op.top() != '(')
				popOp();
			op.pop();
		}
		if(*cur == '+'){
			while(!op.empty() && (op.top() != '('))
				popOp();
			op.push('+');
		}
		if(*cur == '-'){
			char *tmp = cur - 1;
			while(*tmp == ' ' && tmp >= express)
				--tmp;
			if(tmp >= express && (isdigit(*tmp) || *tmp == ')')){
				while(!op.empty() && (op.top() != '('))
					popOp();
				op.push('-');
			}else{
//				putchar('%');
				op.push('%');
			}
		}
		if(*cur == '*'){
			while(!op.empty() && (op.top() != '+' && op.top() != '-' && op.top() != '('))
				popOp();
			op.push('*');
		}
		if(*cur == '/'){
			while(!op.empty() && (op.top() != '+' && op.top() != '-' && op.top() != '('))
				popOp();
			op.push('/');
		}
		if(*cur == '^'){
			while(!op.empty() && op.top() != '(' && op.top() == '%')
				popOp();
			op.push('^');
		}
	}
	while(!op.empty()){
		if(op.top() == '('){
			puts("Error");
			exit(0);
		}
		popOp();
	}
	if(num.size() != 1u){
		puts("Error");
		exit(0);
	}else{
		printf("%lld\n", num.top());
	}
	return 0;
}
