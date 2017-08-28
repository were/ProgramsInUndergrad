#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;

string s;
vector<string> text;

int main(int argc, char *argv[]) {
	if(argc != 2) {
		cout << "usage: ./clean a.cpp" << endl;
		return 1;
	}
	ifstream fin(argv[1]);
	while(getline(fin, s)) {
		text.push_back(s);
	}
	fin.close();
	ofstream fout(argv[1]);
	for(unsigned i = 0; i < text.size(); ++i) if(text[i][0] != '/' || text[i][1] != '/') {
		fout << text[i] << endl;
	}
	return 0;
}
