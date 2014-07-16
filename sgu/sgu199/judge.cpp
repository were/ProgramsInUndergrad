#include <fstream>

std::ifstream ans("answer"), out("output");

int a, b;

int main() {
	ans >> a;
	out >> b;
	if(a != b) {
		puts("Error!");
		for(;;) {}
	}
	puts("Ok!");
	return 0;
}
