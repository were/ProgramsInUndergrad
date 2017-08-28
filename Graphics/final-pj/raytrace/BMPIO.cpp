#include "RGB.h"

#include <fstream>
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class BMPIo {
private:
	void out(int x, int num, ofstream& fout) {
		char buff[5];
		while (num--) {
			buff[0] = x & 255;
			x >>= 8;
			fout.write(buff, 1);
		}
	}
public:
	BMPIo(string file_name, int width, int height, const vector<RGB> &buffer) {
		ofstream fout(file_name.c_str());
		int tmp = width * 3 / 4 * 4;
		if (tmp < width * 3)
			tmp += 4;
		int size = 54 + tmp * height;

		// ===header===
		fout.write("BM", 2);
		out(size, 4, fout);
		out(0, 4, fout);
		out(54, 4, fout);

		// ===info header===
		out(40, 4, fout);
		out(width, 4, fout);
		out(height, 4, fout);
		out(1, 2, fout);
		out(24, 2, fout);
		out(0, 4, fout);
		out(size - 54, 4, fout);
		out(3780, 4, fout);
		out(3780, 4, fout);
		out(0, 4, fout);
		out(0, 4, fout);

		// ===data====
		tmp -= width * 3;
		vector<RGB>::const_iterator cur = buffer.begin();
		for (int i = height; i; --i)
		{
			for (int j = 0; j < width; ++j) {
				out(cur->to_color(), 3, fout);
				++cur;
			}
			out(0, tmp, fout);
		}
	}
};
