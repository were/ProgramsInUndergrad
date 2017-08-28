#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include <cstdio>
#include <cstdlib>
#include <queue>
#include <vector>
#include <utility>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

const int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
const int NUM_REGIONS = 3, COURT_WIDTH = 600, COURT_HEIGHT = 800;

VideoCapture capture;

const Point
		upLeft[] = {Point(263, 110), Point(212, 300), Point(263, 1266)},
		downRight[] = {Point(513, 1266), Point(263, 1266), Point(455, 1438)};

int totalFrame, width, height, flag, fps;

Point _a, _b, a, b;
int hsh[2000][2000];
vector<Mat*> pics;
Mat trans_mat, playground;
vector<Point2f> from, to;

double square(double x) {
	return x * x;
}

uchar find_max_idx(Vec3b &vec) {
	if (vec[0] > vec[1] && vec[0] > vec[2]) {
		return 0;
	}
	if (vec[1] > vec[2] && vec[1] > vec[0]) {
		return 1;
	}
	return 2;
}

bool inRange(int x, int y) {
	for (int k = 0; k < NUM_REGIONS; ++k) {
		if (x >= upLeft[k].x && x < downRight[k].x && y >= upLeft[k].y && y < downRight[k].y) {
			return true;
		}
	}
	return false;
}

pair<Point, Point> bfs(int x, int y, Mat *frame, bool FROM_CLICK) {
	if (FROM_CLICK)
		++flag;
	//cout << x << ", " << y << endl;
	//cout << "Try to bfs..." << endl;
	queue<Point> q;
	int cnt = 0;
	int center_x = 0, center_y = 0;
	int up_x = 9999, up_y = 9999, down_x = 0, down_y = 0;
	for (q.push(Point(x, y)), hsh[x][y] = flag; !q.empty(); q.pop()) {
		++cnt;
		x = q.front().x;
		y = q.front().y;
		//cout << q.front() << endl;
		Vec3b cur = frame->at<Vec3b>(x, y);
		uchar max_idx = find_max_idx(cur);
		for (int i = 0; i < 4; ++i) {
			int _x = x + dx[i], _y = y + dy[i];
			//if (_x >= 0 && _x < height && _y >= 0 && _y < width) {
			if (inRange(_x, _y)) {
				Vec3b nxt = frame->at<Vec3b>(_x, _y);
				bool ok = true;
				for (int j = 0; j < 3; ++j) {
					if (nxt == Vec3b(255, 0, 0)) {
						ok = false;
					}
//					if (abs((int) nxt[j] - (int) cur[j])) {
//						ok = false;
//					}
				}
				if (ok && hsh[_x][_y] != flag) {
					q.push(Point(_x, _y));
					hsh[_x][_y] = flag;
				}
			}
		}
		//frame->at<Vec3b>(x, y) = Vec3b(0, 0, 0);
		up_x = min(up_x, x);
		up_y = min(up_y, y);
		down_x = max(down_x, x);
		down_y = max(down_y, y);
		center_x += x;
		center_y += y;
	}
	center_x /= cnt;
	center_y /= cnt;
	//rectangle(*frame, Point(up_y, up_x), Point(down_y, down_x), Scalar(0, 0, 0));
	//cout << "Totally " << cnt << " floodfilled!" << endl;
	//imshow("T_T", *frame);
	return cnt > 200 ? make_pair(Point(up_y, up_x), Point(down_y, down_x)) : make_pair(Point(-1, -1), Point(-1, -1));
}

void coloring(Mat *frame) {
	for (int k = 0; k < NUM_REGIONS; ++k) {
		for (int i = upLeft[k].y; i < downRight[k].y; ++i) {
			for (int j = upLeft[k].x; j < downRight[k].x; ++j) {
				if ((int) frame->at<Vec3b>(j, i)[0] > 180 && (int) frame->at<Vec3b>(j, i)[1] > 180 &&
					(int) frame->at<Vec3b>(j, i)[2] > 180) {
					continue;
				}
				if ((int) frame->at<Vec3b>(j, i)[1] > 200) {
					frame->at<Vec3b>(j, i) = Vec3b(0, 255, 0);
				}
				if ((int) frame->at<Vec3b>(j, i)[2] > 180) {
					frame->at<Vec3b>(j, i) = Vec3b(0, 0, 255);
				}
			}
		}
	}
}

int find_static(Mat *frame) {
	int cnt = 0;
	for (int k = 0; k < NUM_REGIONS; ++k) {
		for (int i = upLeft[k].y; i < downRight[k].y; ++i) {
			for (int j = upLeft[k].x; j < downRight[k].x; ++j) {
				if (frame->at<Vec3b>(j, i) == Vec3b(0, 0, 255) || frame->at<Vec3b>(j, i) == Vec3b(0, 255, 0)) {
					continue;
				}
				int from = max(0, (int) pics.size() - 5);
				int total = (int) pics.size() - from;
				double chanel[3] = {0, 0, 0}, sqr_vari[3] = {0, 0, 0};
				for (size_t pic_idx = (size_t) from; pic_idx < pics.size(); ++pic_idx) {
					for (uchar cha_idx = 0; cha_idx < 3; ++cha_idx) {
						chanel[cha_idx] += pics[pic_idx]->at<Vec3b>(j, i)[cha_idx];
					}
				}
				for (size_t pic_idx = (size_t) from, div = (size_t) total; pic_idx < pics.size(); ++pic_idx, --div) {
					for (uchar cha_idx = 0; cha_idx < 3; ++cha_idx) {
						sqr_vari[cha_idx] += square(pics[pic_idx]->at<Vec3b>(j, i)[cha_idx] - chanel[cha_idx] / total) / (double) (div * div);
					}
				}
				for (int cha_idx = 0; cha_idx < 3; ++cha_idx) {
					sqr_vari[cha_idx] /= 2;
				}
				if (sqr_vari[0] + sqr_vari[1] + sqr_vari[2] < 15.) {
					/*
					cout << j << ", " << i << ": " << sqr_vari[0] << ", " << sqr_vari[1] << ", " << sqr_vari[2] << endl;
					cout << j << ", " << i << ": " << chanel[0] << ", " << chanel[1] << ", " << chanel[2] << endl;
					 */
					frame->at<Vec3b>(j, i) = Vec3b(255, 0, 0);
				} else {
					//cout <<  sqr_vari[0] + sqr_vari[1] + sqr_vari[2]  << endl;
					++cnt;
				}
			}
		}
	}
	return cnt;
}

static void onMouse(int event, int x, int y, int flags, void *para) {
	Mat *frame = (Mat *) para;
	switch(event){
		case EVENT_LBUTTONDOWN: {
			//cout << "Click on " << x << ", " << y << endl;
			_a = Point(x, y);
			break;
		}
		case EVENT_LBUTTONUP: {
			//cout << "Release at " << x << ", " << y << endl;
			if (x == _a.x || y == _a.y) {
				cout << height - _a.y << ", " << _a.x << endl;
				cout << _a.y << ", " << _a.x << endl;
				cout << frame->at<Vec3b>(y, x) << endl;
				bfs(y, x, frame, true);
				//rectangle(*frame, Point(x - 100, y - 100), Point(x + 100, y + 100), Scalar(0, 0, 0));
				imshow("T_T", *frame);
				waitKey(0);
				break;
			}
			_b = Point(x, y);
			a = Point(min(_a.x, _b.x), min(_a.y, _b.y));
			b = Point(max(_a.x, _b.x), max(_a.y, _b.y));
			//cout << Point(height - a.x, a.y) << Point(height - b.x, b.y) << endl;
			cout << a << ", " << b << endl;
			//Mat select = frame->rowRange(a.y, b.y).colRange(a.x, b.x);
			rectangle(*frame, a, b, Scalar(0));
			imshow("T_T", *frame);
			break;
		}
		default: {
			//cout << x << ", " << y << endl;
			break;
		}
	}
}

int calcRadius(Point a, Point b) {
	double area;
	area = (double) abs((b.x - a.x) * (b.y - a.y));
	area *= (double) (COURT_WIDTH * COURT_HEIGHT) / (double) (width * height);
	return max((int)sqrt(area) / 2, 2);
}

void workOnIt(Mat *frame, Mat *screen) {
	++flag;
	vector<Point2f> camera, world;
	vector<int> radius;
	for (int k = 0; k < NUM_REGIONS; ++k) {
		for (int i = upLeft[k].y; i < downRight[k].y; ++i) {
			for (int j = upLeft[k].x; j < downRight[k].x; ++j) {
				if (hsh[j][i] != flag && (frame->at<Vec3b>(j, i) == Vec3b(0, 255, 0) || frame->at<Vec3b>(j, i) == Vec3b(0, 0, 255))) {
					pair<Point, Point> rect = bfs(j, i, frame, false);
					if (rect.first != Point(-1, -1)) {
						rectangle(*screen, rect.first, rect.second, Scalar(0, 0, 0));
						Point center = rect.first + rect.second;
						camera.push_back(Point2f(center.x / 2, center.y / 2));
						radius.push_back(calcRadius(rect.first, rect.second));
					}
				}
			}
		}
		cout << k << " done..." << endl;
	}
	Mat thisFrame;
	playground.copyTo(thisFrame);
}

Mat transRealWorld(Mat img) {
	Mat res = Mat::zeros(COURT_HEIGHT, COURT_WIDTH, CV_8UC3);
	for (size_t i = 0; i < from.size(); ++i) {
		int x = (int) to[i].x, y = (int) to[i].y;
		if (0 <= x && x < COURT_HEIGHT && y >= 0 && y < COURT_WIDTH) {
			res.at<Vec3b>(x, y) = img.at<Vec3b>((int) from[i].x, (int) from[i].y);
		}
	}
	return res;
}

void processEveryFrame() {
	Mat frame, screen;
	for (int _ = 0; _ < totalFrame; ++_) {
		capture >> frame;
		frame.copyTo(screen);
		Mat *for_push = new Mat();
		char filename[20];
		frame.copyTo(*for_push);
		pics.push_back(for_push);
		coloring(&frame);
		//bool stop = false;
		vector<Point2f> camera, world;
		vector<int> radius;
		if (_) {
			find_static(&frame);
			++flag;
			for (int k = 0; k < NUM_REGIONS; ++k) {
				for (int i = upLeft[k].y; i < downRight[k].y; ++i) {
					for (int j = upLeft[k].x; j < downRight[k].x; ++j) {
						if (hsh[j][i] != flag && (frame.at<Vec3b>(j, i) == Vec3b(0, 255, 0) || frame.at<Vec3b>(j, i) == Vec3b(0, 0, 255))) {
							pair<Point, Point> rect = bfs(j, i, &frame, false);
							if (rect.first != Point(-1, -1)) {
								rectangle(screen, rect.first, rect.second, Scalar(0, 0, 0));
								Point center = rect.first + rect.second;
								camera.push_back(Point2f(center.y / 2, center.x / 2));
								radius.push_back(calcRadius(rect.first, rect.second));
							}
						}
					}
				}
				cout << k << " done..." << endl;
			}
			Mat thisFrame;
			playground.copyTo(thisFrame);
			perspectiveTransform(camera, world, trans_mat);
			for (size_t i = 0; i < world.size(); ++i) {
				if (world[i].x >= 0 && world[i].x < COURT_HEIGHT && world[i].y >= 0 && world[i].y < COURT_WIDTH) {
					circle(thisFrame, Point((int) world[i].y, (int) world[i].x), radius[i], 1);
//					cout << world[i].y << ", " << world[i].x << endl;
				}
			}
//			imshow("T_T", thisFrame);
//			waitKey(0);
			sprintf(filename, "track-%03d.jpg", _);
			imwrite(filename, thisFrame);
		}
		sprintf(filename, "res-%03d.jpg", _);
		imwrite(filename, screen);
		Mat tmp = transRealWorld(screen);
		for (size_t i = 0; i < world.size(); ++i) {
			if (world[i].x >= 0 && world[i].x < COURT_HEIGHT && world[i].y >= 0 && world[i].y < COURT_WIDTH) {
				circle(tmp, Point((int) world[i].y, (int) world[i].x), radius[i], 1);
				//cout <<  (world[i].y >= 0 && world[i].y < COURT_HEIGHT && world[i].x >= 0 && world[i].x < COURT_WIDTH) << endl;
				//cout << world[i].y << ", " << world[i].x << endl;
			}
		}
		sprintf(filename, "twist-%03d.jpg", _);
		imwrite(filename, tmp);
		//imshow("T_T", tmp);
//		setMouseCallback("T_T", onMouse, (void *) &tmp);
		//waitKey(0);
		//waitKey(1000 / fps);
		printf("%d\n", _);
	}
	system("rm res.avi");
	system("rm track.avi");
	system("rm twist.avi");
	system("ffmpeg -f image2 -framerate 29 -i res-%03d.jpg -s 1696x1080 -vb 9M res.avi");
	system("ffmpeg -f image2 -framerate 29 -i track-%03d.jpg -s 800x600 -vb 1M track.avi");
	system("ffmpeg -f image2 -framerate 29 -i twist-%03d.jpg -s 800x600 -vb 1M twist.avi");
	system("rm *-*.jpg");
	//system("rm track-*.jpg");
	while (pics.size()) {
		delete pics.back();
		pics.pop_back();
	}
}

void init() {
	capture.open("1.mp4");
	totalFrame = (int) capture.get(CV_CAP_PROP_FRAME_COUNT);
	fps = capture.get(CV_CAP_PROP_FPS);
	width = (int) capture.get(CV_CAP_PROP_FRAME_WIDTH);
	height = (int) capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	cout << Size(width, height) << endl;
}

void calcTransform() {
	Mat img=imread("playground.jpg");
	int img_height = img.rows;
	int img_width = img.cols;
	vector<Point2f> camera;
	camera.push_back(Point2f(342, -329));
	camera.push_back(Point2f(197, 581));
	camera.push_back(Point2f(929, 446));
	camera.push_back(Point2f(265, 1650));
	vector<Point2f> world;
	world.push_back(Point2f(0, 0));
	world.push_back(Point2f(0, COURT_WIDTH - 1));
	world.push_back(Point2f(COURT_HEIGHT - 1, 0));
	world.push_back(Point2f(COURT_HEIGHT - 1, COURT_WIDTH - 1));

	trans_mat = getPerspectiveTransform(camera, world);
	//cout<<transform<<endl;
	playground = Mat::zeros(COURT_HEIGHT, COURT_WIDTH, CV_8UC3);
	for (int i = 0; i < COURT_HEIGHT; ++i) {
		for (int j = 0; j < COURT_WIDTH; ++j) {
			playground.at<Vec3b>(i, j) = Vec3b(0, 255, 150);
		}
	}

	for(int i = 0; i < img_height; i++){
		for(int j = 0; j < img_width; j++){
			from.push_back(Point2f(i, j));
		}
	}
	perspectiveTransform(from, to, trans_mat);
	cout << "???" << endl;
//	for (size_t i = 0; i < from.size(); ++i) {
//		int x = (int) to[i].x, y = (int) to[i].y;
//		if (0 <= x && x < COURT_HEIGHT && y >= 0 && y < COURT_WIDTH) {
//			playground.at<Vec3b>(x, y) = img.at<Vec3b>((int) from[i].x, (int) from[i].y);
//		}
//	}

	rectangle(playground, Point(120, 660), Point(440, 800), Scalar(0, 0, 0), 2);
	rectangle(playground, Point(185, 735), Point(370, 800), Scalar(0, 0, 0), 2);
	line(playground, Point(0, 400), Point(600, 400), Scalar(0, 0, 0), 2);
	circle(playground, Point(287, 400), 60, Scalar(0, 0, 0), 2);
	ellipse(playground, Point(285, 690), Size(80, 80), 0, 340, 200, Scalar(0, 0, 0), 2);

//	imshow("T_T", playground);
//	setMouseCallback("T_T", onMouse, (void *) &playground);
//	waitKey(0);
//	imwrite("res.jpg", playground);
}

int main() {
	init();
	calcTransform();
	processEveryFrame();
	return 0;
}
