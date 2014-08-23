#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int main(int argv, char*argc[]){
	if(argv == 2){
		std::ifstream fin(argc[1]);
		std::string tmp;
		std::vector<std::string> file;
		while(std::getline(fin, tmp))
			if(tmp[0] == '/' && tmp[1] == '/')
				continue;
			else
				file.push_back(tmp);
		fin.close();
		std::ofstream fout(argc[1]);
		for(unsigned i = 0;i < file.size();++i)
			fout << file[i] << std::endl;
	}else
		std::cerr << "Usage: clear.exe work.cpp" << std::endl;
	return 0;
}
