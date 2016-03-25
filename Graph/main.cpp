#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>

using std::cout;
using std::ostream;
using std::endl;
using std::ofstream;
using std::min;
using std::string;
using std::vector;

const double INF = 1e20, EPS = 1e-9;

struct Vec3 {
	double x, y, z;

	Vec3() : x(0.), y(0.), z(0.) {}
	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

	Vec3 operator+ (const Vec3 &b) const{
		return Vec3(x + b.x, y + b.y, z + b.z);
	}

	Vec3 operator- (const Vec3 &b) const {
		return Vec3(x - b.x, y - b.y, z - b.z);
	}

	Vec3 operator* (const double &b) const {
		return Vec3(b * x, b * y, b * z);
	}

	Vec3 mul(const Vec3 &b) const {
		return Vec3(x * b.x, y * b.y, z * b.z);
	}

	double dot(const Vec3 &b) const {
		return x * b.x + y * b.y + z * b.z;
	}

	Vec3 cross(const Vec3 &b) const {
		return Vec3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}

	Vec3 one() {
		double len = sqrt(dot(*this));
		return Vec3(x / len, y / len, z / len);
	}

	int to_color() const {
		return ((int) (min(1., x) * 255.) << 16) | 
			((int) (min(1., y) * 255.) << 8) | ((int) (min(1., z) * 255.));
	}
};

ostream &operator<< (ostream &out, const Vec3 &data) {
	return out << "(" << data.x << ", " << data.y << ", " << data.z << ")";
}

Vec3 operator* (const double &a, const Vec3 &b) {
	return Vec3(a * b.x, a * b.y, a * b.z);
}

struct Ray {
	Vec3 o, dir;
	Ray() {}
	Ray(const Vec3 &a, const Vec3 &b) : o(a), dir(b) {
		dir = dir.one();
	}
	Vec3 get_point(double t) const {
		return o + t * dir;
	}
};

struct Material {
	Vec3 env, diff, spec;
	double coef_n, coef_ref;
};

struct Object {
	Material mat;
	virtual double hit(const Ray &ray) = 0;
	virtual Vec3 normal(const Ray &ray, const Vec3 &point) = 0;
};

struct Surface : public Object {
	Vec3 n;
	Vec3 normal(const Ray &ray, const Vec3 &point) {
		if (ray.dir.dot(n) > 0) {
			return n * -1;
		}
		return n;
	}
};

double det(const Vec3 &x, const Vec3 &y, const Vec3 &z) {
	double d11 = x.x * (y.y * z.z - z.y * y.z);
	double d22 = y.x * (x.y * z.z - z.y * x.z);
	double d33 = z.x * (x.y * y.z - y.y * x.z);
	return d11 - d22 + d33;
}

struct Triangle : public Surface {
	Vec3 a, b, c, ba, ca;

	Triangle() {}

	Triangle(Vec3 &a, Vec3 &b, Vec3 &c) : a(a), b(b), c(c), ba(a - b), ca(a - c) {
		n = ba.cross(ca).one();
	}

	double hit(const Ray &ray) {
		double A = det(ba, ca, ray.dir);
		if (A != 0) {
			Vec3 v = a - ray.o;
			double beta = det(v, ca, ray.dir) / A;
			double gama = det(ba, v, ray.dir) / A;
			if (beta > 0 && gama > 0 && beta + gama < 1) {
				return det(ba, ca, v) / A;
			}
		}
		return INF;
	}
};

struct Rectangle : public Surface {
	Vec3 start, d1, d2;

	Rectangle() {}

	Rectangle(Vec3 &start, Vec3 &d1, Vec3 &d2) : start(start), d1(d1), d2(d2) {
		n = d1.cross(d2).one();
	}

	double hit(const Ray &ray) {
		double A = det(d1, d2, ray.dir);
		if (A != 0) {
			Vec3 v = ray.o - start;
			double beta = det(v, d2, ray.dir) / A;
			double gama = det(d1, v, ray.dir) / A;
			if (beta >= 0 && gama >= 0 && beta <= 1 && gama <= 1) {
				return -det(d1, d2, v) / A;
			}
		}
		return INF;
	}

};

struct Sphere : public Object {
	Vec3 o;
	double r;
	Sphere() {}
	Sphere(double x, double y, double z, double r) : o(x, y, z), r(r) {}
	double hit(const Ray &ray) {
		Vec3 v = ray.o - o;
		double dv = ray.dir.dot(v);
		double delta = dv * dv - v.dot(v) + r * r;
		return delta > 0 ? -dv - sqrt(delta) : INF;
	}
	Vec3 normal(const Ray &ray, const Vec3 &point) {
		return (point - o).one();
	}
};

struct BMPIo {
	void out(int x, int num, ofstream& fout) {
		char buff[5];
		while (num--) {
			buff[0] = x & 255;
			x >>= 8;
			fout.write(buff, 1);
		}
	}
	
	BMPIo(string file_name, int width, int height, const vector<Vec3> &buffer) {
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
		vector<Vec3>::const_iterator cur = buffer.begin();
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

struct Camera {
	Vec3 pos, up, right;
	int half_width, half_height;

	Camera() {}

	Camera(int w, int h, Vec3 pos, Vec3 dir) : pos(pos), half_width(w / 2), half_height(h / 2) {
		Vec3 front = (-1 * pos).one();
		cout << dir.dot(front) << endl;
		right = dir.one() * .2;
		up = front.cross(right);
		up = up.one() * .2;
	}

	Ray cast(double x, double y) {
		return Ray(
			pos,
			Vec3(right * x + up * y - pos).one()
		);
	}

	int total_pixel() {
		return half_width * half_height * 4;
	}
};

struct Light {
	Vec3 pos, color;
	Light() {}
	Light(const Vec3 &a, const Vec3 &b) : pos(a), color(b) {}
};

struct Main {
	int max_depth;
	vector<Object*> objs;
	vector<Vec3> buffer;
	vector<Light> lights;
	Camera camera;
	Vec3 env;

	Main() {
		max_depth = 22;
		camera = Camera(1600, 1200, Vec3(0, 50, 50), Vec3(-1, -1, 1));
		buffer.resize(camera.total_pixel());
	}

	Vec3 shading(const Object *obj, const Ray &ray, const Vec3 &point, 
			const Vec3 &normal, int depth) {
		Vec3 res(obj->mat.env.mul(env));
		for (auto &pl : lights) {
			Ray sRay;
			sRay.o = point;
			sRay.dir = (pl.pos - point).one();
			
			double cos_theta = normal.dot(sRay.dir);
			if (cos_theta > 0) {
				double limit_t = 0;
				if (pl.pos.x != point.x) {
					limit_t = (pl.pos.x - point.x) / sRay.dir.x;
				}
				else if (pl.pos.y != point.y) {
					limit_t = (pl.pos.y - point.y) / sRay.dir.y;
				}
				else {
					limit_t = (pl.pos.z - point.z) / sRay.dir.z;
				}
				bool shadow = false;
				for (auto &other_obj : objs) {
					if (other_obj != obj) {
						double t = other_obj->hit(sRay);
						if (EPS < t && t < limit_t) {
							shadow = true;
							break;
						}
					}
				}
				if (!shadow) {
					Vec3 tmp(pl.pos - point);
					double dis_square = tmp.dot(tmp);
					double f = 1.0 / (0.00005 * dis_square);
					if (f > 1) {
						f = 1.0;
					}
					res = res + pl.color.mul(obj->mat.diff * cos_theta + 
							obj->mat.spec * pow(cos_theta, obj->mat.coef_n));
				}
			}
		}
		if (depth < max_depth) {
			if (obj->mat.coef_ref > EPS) {
				Ray rRay;
				rRay.o = point;
				rRay.dir = ray.dir - normal * (ray.dir.dot(normal) * 2);
				res = res + raytrace(rRay, depth + 1) * obj->mat.coef_ref;
			}
		}
		return res;
	}

	Vec3 raytrace(const Ray &ray, int depth) {
		double dis = INF;
		Object *target = NULL;
		for (auto &obj : objs) {
			double tmp = obj->hit(ray);
			if (EPS < tmp && tmp < dis) {
				dis = tmp;
				target = obj;
			}
		}
		if (target) {
			Vec3 point(ray.get_point(dis));
			return shading(target, ray, point, target->normal(ray, point), depth);
		}
		return Vec3(0, 0, 0);
	}

	void render() {
		import("config");
		cout << "config done.." << endl;
		int cur_pixel = 0;
		for (int i = -camera.half_height; i < camera.half_height; ++i) {
			for (int j = -camera.half_width; j < camera.half_width; ++j) {
				buffer[cur_pixel++] = raytrace(camera.cast(i, j), 0);
			}
		}
		BMPIo("res.bmp", camera.half_width * 2, camera.half_height * 2, buffer);
	}

	void import(const char *scenefile) {
		FILE *fp = fopen(scenefile, "rb");
		char tag[64];
		fscanf(fp, "%s", tag);

		vector<Material> mtls;
		do {
			Material mtl;
			fscanf(fp, "\tambient %lf %lf %lf", &mtl.env.x, &mtl.env.y, &mtl.env.z);
			fscanf(fp, "\tdiffuse %lf %lf %lf", &mtl.diff.x, &mtl.diff.y, &mtl.diff.z);
			fscanf(fp, "\tspecular %lf %lf %lf", &mtl.spec.x, &mtl.spec.y, &mtl.spec.z);
			fscanf(fp, "\tn %lf", &mtl.coef_n);
			fscanf(fp, "\treflection %lf", &mtl.coef_ref);
			mtls.push_back(mtl);
			fscanf(fp, "%s", tag);
		} while (strcmp(tag, "Material") == 0);

		while (strcmp(tag, "Light") != 0) {
			bool ignorance = tag[0] == '#';
			if (ignorance) {
				int len = strlen(tag) - 1;
				for (int i = 0; i < len; ++i) {
					tag[i] = tag[i+1];
				}
				tag[len] = 0;
			}

			Object *obj = NULL;
			if (strcmp(tag, "Sphere") == 0) {
				double x, y, z, r;
				fscanf(fp, "\tcenter %lf %lf %lf", &x, &y, &z);
				fscanf(fp, "\tradius %lf", &r);
				obj = new Sphere(x, y, z, r);
			}
			else if (strcmp(tag, "Rectangle") == 0) {
				Vec3 s, d1, d2;
				fscanf(fp, "\tstart %lf %lf %lf", &s.x, &s.y, &s.z);
				fscanf(fp, "\td1 %lf %lf %lf", &d1.x, &d1.y, &d1.z);
				fscanf(fp, "\td2 %lf %lf %lf", &d2.x, &d2.y, &d2.z);
				obj = new Rectangle(s, d1, d2);
			}
			else if (strcmp(tag, "Triangle") == 0) {
				Vec3 a, b, c;
				fscanf(fp, "\td1 %lf %lf %lf", &a.x, &a.y, &a.z);
				fscanf(fp, "\td2 %lf %lf %lf", &b.x, &b.y, &b.z);
				fscanf(fp, "\td3 %lf %lf %lf", &c.x, &c.y, &c.z);
				obj = new Triangle(a, b, c);
			}

			int mtl_index;
			fscanf(fp, "\tmaterial %d", &mtl_index);
			obj->mat = mtls[mtl_index];
			if (ignorance) {
				delete obj;
			} else {
				objs.push_back(obj);
			}
			fscanf(fp, "%s", tag);
		}

		fscanf(fp, "\tAmbient %lf %lf %lf", &env.x, &env.y, &env.z);

		while (fscanf(fp, "%s", tag) != EOF) {
			bool ignorance = tag[0] == '#';
			if (ignorance) {
				int len = strlen(tag) - 1;
				for (int i = 0; i + 1 < len; ++i) {
					tag[i] = tag[i + 1];
				}
				tag[len] = 0;
			}

			Light pl;
			fscanf(fp, "\tposition %lf %lf %lf", &pl.pos.x, &pl.pos.y, &pl.pos.z);
			fscanf(fp, "\tintensity %lf %lf %lf", &pl.color.x, &pl.color.y, &pl.color.z);

			if (!ignorance) {
				lights.push_back(pl);
			}
		}

		fclose(fp);
	}


};

int main() {
	Main().render();
	return 0;
}
