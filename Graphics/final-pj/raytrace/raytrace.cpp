#include "BMPIO.cpp"

#include <cmath>
#include <cassert>

using namespace std;

const double EPS = 1e-8;
const double INF = 1e100;

class Point {
public:
	double x, y, z;
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
	Point() {}

	friend inline Point operator +(const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}
	friend inline Point operator -(const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}
	friend inline Point operator *(const Point &a, double k) {
		return Point(a.x * k, a.y * k, a.z * k);
	}
	friend inline Point operator *(double k, const Point &a) {
		return Point(a.x * k, a.y * k, a.z * k);
	}
	friend inline Point operator /(const Point &a, double k) {
		return Point(a.x / k, a.y / k, a.z / k);
	}

	double dot(const Point &o) const {
		return x * o.x + y * o.y + z * o.z;
	}
	Point det(const Point &o) const {
		//  x   y   z
		//o.x o.y o.z
		return Point(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
	}

	Point normal() {
		double l = sqrt(this->dot(*this));
		return Point(x / l, y / l, z / l);
	}

	double dist2(const Point &o) {
		return (*this - o).dot(*this - o);
	}

	double dist(const Point &o) {
		return sqrt(this->dist2(o));
	}
};

class Light {
public:
	RGB color; Point o;
	Light(RGB color, Point o) : color(color), o(o) {};
	Light(){}
};

class Ray {
public:
	Point o, dir;
	Ray(Point o, Point dir) : o(o), dir(dir) {
		this->dir = this->dir.normal();
	}
	Ray() {}
	Point get_point(double dist) {
		return o + dir * dist;
	}
};

struct Material {
	RGB env, diff, spec, refr;
	double coef_n, coef_reflect, coef_refract, coef_eta;
};

class Object {
public:
	Object() {}
	Material mat;
	virtual double hit(const Ray& ray) = 0;
	virtual Point normal(const Ray &ray, const Point &point) = 0;
	virtual bool contain(const Point &point) = 0;
};

class Surface : public Object {
public:
	Surface() {}
	Point n;
	Point normal(const Ray &ray, const Point &point) {
		if (ray.dir.dot(n) > 0) {
			return n * -1;
		}
		return n;
	}
	bool contain(const Point &point) {
		return false;
	}
};

ostream &operator<< (ostream &out, const Point &data) {
	return out << "(" << data.x << ", " << data.y << ", " << data.z << ")";
}

double det(const Point &a, const Point &b, const Point &c) {
	return a.x * (b.y * c.z - b.z * c.y) -
		   a.y * (b.x * c.z - b.z * c.x) +
		   a.z * (b.x * c.y - b.y * c.x);
	//Point(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
}

class Triangle : public Surface {
public:
	Point a, b, c;
	Triangle() {}
	Triangle(Point a, Point b, Point c) : a(a), b(b), c(c) {
		n = ((a - b).det(a - c)).normal();
	}

	double hit(const Ray& ray) {
		Point ba = (a - b), ca = (a - c);
		double A = det(ba, ca, ray.dir);
		if (A != 0) {
			Point v = a - ray.o;
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
	Point start, d1, d2;

	Rectangle() {}

	Rectangle(Point &start, Point &d1, Point &d2) : start(start), d1(d1), d2(d2) {
		n = d1.det(d2).normal();
	}

	double hit(const Ray &ray) {
		double A = det(d1, d2, ray.dir);
		if (A != 0) {
			Point v = ray.o - start;
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
	Point o;
	double r;
	Sphere() {}
	Sphere(double x, double y, double z, double r) : o(x, y, z), r(r) {}
	double hit(const Ray &ray) {
		Point v = ray.o - o;
		double dv = ray.dir.dot(v);
		double delta = dv * dv - v.dot(v) + r * r;
		//return delta > 0 ? -dv - delta : INF;
		if (delta < 0) {
			return INF;
		} else {
			delta = sqrt(max(0., delta));
			if (-dv - delta > EPS) {
				return -dv - delta;
			} else if (-dv + delta > EPS) {
				return -dv + delta;
			} else {
				return INF;
			}
		}
	}
	bool contain(const Point &point) {
		if (o.dist(point) < r) {
			return true;
		} else {
			return false;
		}
	}
	Point normal(const Ray &ray, const Point &point) {
		Point ret = (point - o).normal();
		if (contain((ray.o + point) / 2)) {
			ret = -1. * ret;
		}
		return ret;
	}
};


class Camera {
public:
	Point pos, up, right;
	int half_width, half_height, width, height;

	Camera() {}

	Camera(int w, int h, Point pos, Point dir, double scale) : pos(pos), half_width(w / 2), half_height(h / 2){
		Point front = (Point(0, 0, 0) - pos).normal();
		right = dir.normal() * scale;
		up = front.det(right).normal() * scale;

		width = w, height = h;
	}

	Ray cast(double y, double x) {
		Point pos(Point(50,48,295.6));
		Point dir(0,-0.042612,-1);
		dir.normal();
		Point cx(width * .5135 / height, 0, 0);
		Point cy = cx.det(dir).normal() * .5135;
		Point d = cx * ((x + 0.5) / width - 0.5) + cy * (-(y + 0.5) / height + 0.5)+ dir;
		//printf("cx: %f\n", cx.dot(dir));
		//printf("cy: %f\n", cy.dot(dir));
		return Ray(
			pos + d * 140, d
		);
	}
};

class RayTrace {
private:
	int MAX_DEPTH;
	vector<Object*> objects;
	vector<Light> lights;
	Camera camera;

	RGB env;

	RGB shading(Object *obj, Ray ray, Point cur, Point norm, int depth, double weaken) {
		RGB color = env * obj->mat.env;
		if (weaken < 0.01) {
			return color;
		}

		Ray rRay(cur, ray.dir - norm * (ray.dir.dot(norm) * 2));
		bool inside = obj->contain((ray.o + cur) / 2.);
		Ray tRay;
		{
			double eta = inside ? (1. / obj->mat.coef_eta) : (obj->mat.coef_eta);
			Point m = eta * (norm * norm.dot(rRay.dir) - rRay.dir);
			Point t = m - (norm * norm.dot(rRay.dir));
			tRay = Ray(cur, t);
		}
		// 与光直接接触产生的贡献
		for (auto &lig : lights) {
			Ray sRay(cur, lig.o - cur);
			double cos_theta = sRay.dir.dot(norm);

			double dist_to_light = lig.o.dist(cur);
			bool is_blocked = false;
			for (auto &other_obj : objects) {
				if (obj == other_obj) {
					continue;
				}

				double dist = other_obj->hit(sRay);
				if (EPS < dist && dist < dist_to_light) {
					is_blocked = true;
				}
			}

			if (!is_blocked) {
				double dist_coef = min(1., 1 / (0.00005 * lig.o.dist2(cur)));
				if (!inside && cos_theta > 0) {
					color += dist_coef * lig.color * obj->mat.diff * cos_theta; // diffuse
					color += dist_coef * lig.color * obj->mat.spec * pow(max(1., rRay.dir.dot(sRay.dir)), obj->mat.coef_n);
					// specular reflection
				}
				if (cos_theta < 0) {
					color += dist_coef * lig.color * obj->mat.refr * pow(max(1., tRay.dir.dot(sRay.dir)), 1); // refract
				}
			} else {
				//printf("Shadow!\n");
			}
		}

		// 通过其他物体的反射
		if (depth < MAX_DEPTH) {
			if (obj->mat.coef_reflect > EPS) {
				color += trace(rRay, depth + 1, weaken * obj->mat.coef_reflect) * obj->mat.coef_reflect;
			}
			if (obj->mat.coef_refract > EPS) {
				color += trace(tRay, depth + 1, weaken * obj->mat.coef_refract) * obj->mat.coef_refract;
			}
		}
		return color;
	}

	RGB trace(Ray ray, int depth, double weaken) {
		double min_dist = 1e100;
		Object* target = NULL;

		for (auto &obj : objects) {
			double dist = obj->hit(ray);
			if (EPS < dist && dist < min_dist) {
				min_dist = dist;
				target = obj;
			}
		}

		if (target != NULL) {
			Point p = ray.get_point(min_dist);
			return shading(target, ray, p, target->normal(ray, p), depth, weaken);
		} else {
			return env;
		}
	}

public:
	RayTrace() {
		MAX_DEPTH = 12;
		int SCALE = 2;
		camera = Camera(1024 / SCALE, 768 / SCALE, Point(50, 48, 295.6), Point(0, -0.042612, 1), SCALE * .04);
	}
	void import(const char *scenefile) {
		FILE *fp = fopen(scenefile, "rb");
		char tag[64];
		fscanf(fp, "%s", tag);

		vector<Material> mtls;
		do {
			Material mtl;
			fscanf(fp, "\tambient %lf %lf %lf", &mtl.env.r, &mtl.env.g, &mtl.env.b);
			fscanf(fp, "\tdiffuse %lf %lf %lf", &mtl.diff.r, &mtl.diff.g, &mtl.diff.b);
			fscanf(fp, "\tspecular %lf %lf %lf", &mtl.spec.r, &mtl.spec.g, &mtl.spec.b);
			fscanf(fp, "\trefract %lf %lf %lf", &mtl.refr.r, &mtl.refr.g, &mtl.refr.b);
			fscanf(fp, "\tn %lf", &mtl.coef_n);
			fscanf(fp, "\treflection %lf", &mtl.coef_reflect);
			fscanf(fp, "\trefraction %lf", &mtl.coef_refract);
			fscanf(fp, "\teta %lf", &mtl.coef_eta);
			//cout << tag << endl;
			mtls.push_back(mtl);
			fscanf(fp, "%s", tag);
		} while (strcmp(tag, "Material") == 0);

		while (strcmp(tag, "Light") != 0) {

			Object *obj = NULL;
			if (strcmp(tag, "Sphere") == 0) {
				double x, y, z, r;
				fscanf(fp, "\tcenter %lf %lf %lf", &x, &y, &z);
				fscanf(fp, "\tradius %lf", &r);
				obj = new Sphere(x, y, z, r);
			}
			else if (strcmp(tag, "Rectangle") == 0) {
				Point s, d1, d2;
				fscanf(fp, "\tstart %lf %lf %lf", &s.x, &s.y, &s.z);
				fscanf(fp, "\td1 %lf %lf %lf", &d1.x, &d1.y, &d1.z);
				fscanf(fp, "\td2 %lf %lf %lf", &d2.x, &d2.y, &d2.z);
				obj = new Rectangle(s, d1, d2);
			}
			else if (strcmp(tag, "Triangle") == 0) {
				Point a, b, c;
				fscanf(fp, "\td1 %lf %lf %lf", &a.x, &a.y, &a.z);
				fscanf(fp, "\td2 %lf %lf %lf", &b.x, &b.y, &b.z);
				fscanf(fp, "\td3 %lf %lf %lf", &c.x, &c.y, &c.z);
				obj = new Triangle(a, b, c);
			}

			int mtl_index;
			fscanf(fp, "\tmaterial %d", &mtl_index);
			obj->mat = mtls[mtl_index];
			objects.push_back(obj);
			fscanf(fp, "%s", tag);
		}

		fscanf(fp, "\tAmbient %lf %lf %lf", &env.r, &env.g, &env.b);

		while (fscanf(fp, "%s", tag) != EOF) {
			if (!strcmp("PointLight", tag)) {
				Light pl;
				fscanf(fp, "\tposition %lf %lf %lf", &pl.o.x, &pl.o.y, &pl.o.z);
				fscanf(fp, "\tintensity %lf %lf %lf", &pl.color.r, &pl.color.g, &pl.color.b);
				lights.push_back(pl);
			}
			else if(!strcmp("PlaneLight", tag)) {
				Point s, d1, d2, cross;
				Light pl;
				fscanf(fp, "\tstart %lf %lf %lf", &s.x, &s.y, &s.z);
				fscanf(fp, "\td1 %lf %lf %lf", &d1.x, &d1.y, &d1.z);
				fscanf(fp, "\td2 %lf %lf %lf", &d2.x, &d2.y, &d2.z);
				fscanf(fp, "\tintensity %lf %lf %lf", &pl.color.r, &pl.color.g, &pl.color.b);
				cross = d1.det(d2);
				double area = sqrt(cross.dot(cross)) + 1.;
				pl.color = pl.color * (1 / area);
				for (int i = 0, _end = (int)  area; i < _end; ++i) {
					double a = (double) (rand()) / RAND_MAX,
						   b = (double) (rand()) / RAND_MAX;
					pl.o = s + d1 * a + d2 * b;
					lights.push_back(pl);
				}
			}
		}

		fclose(fp);
	}

	void render() {
		import("config");
		vector<RGB> buffer;

		int height_block = camera.height / 10;

		cout << "Render start!" << endl;
/*
		for (int i = -camera.half_height, cur = 0; i < camera.half_height; i++, cur++) {
			for (int j = -camera.half_width; j < camera.half_width; j++) {
				//cerr << "(" << i << ", " << j << ")" << endl;
				buffer.push_back(trace(camera.cast(i, j), 0, 1));
			}
			if (cur && cur % height_block == 0) {
				printf("process...                %.1f%%\n", .5 * cur / camera.half_height * 100);
				BMPIo tmp("sample.bmp", camera.width, cur, buffer);
			}
		}*/
		for (int i = camera.height - 1, cur = 0; i >= 0; --i, cur++) {
			for (int j = 0; j < camera.width; j++) {
				//cerr << "(" << i << ", " << j << ")" << endl;
				buffer.push_back(trace(camera.cast(i, j), 0, 1));
			}
			if (cur && cur % height_block == 0) {
				printf("process...                %.1f%%\n", .5 * cur / camera.half_height * 100);
				BMPIo tmp("sample.bmp", camera.width, cur, buffer);
			}
		}
		//RGB tmp = trace(camera.cast(-1, -1), 0);
		//cout << tmp.r << " " << tmp.g << " " << tmp.b << endl;
		cerr << "buffer done" << endl;

		BMPIo bmp("sample.bmp", camera.width, camera.height, buffer);
		cerr << "output done" << endl;
	}
};

int main() {
	RayTrace r;
	r.render();
	return 0;
}
