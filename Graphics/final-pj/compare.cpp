// expanded smallppm (code is exactly the same as smallppm.cpp but with more comments)

#include <math.h>   // smallppm, Progressive Photon Mapping by T. Hachisuka
#include <stdlib.h> // originally smallpt, a path tracer by Kevin Beason, 2008
#include <stdio.h>  // Usage: ./smallppm 100000 && xv image.ppm
#include <algorithm>
#include <assert.h>
#define PI ((double)3.14159265358979) // ^^^^^^:number of photons emitted
#define ALPHA ((double)0.7) // the alpha parameter of PPM

#include <fstream>
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ofstream;
using std::max;
using std::min;

// Halton sequence with reverse permutation
int primes[61]= {
		2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79,
		83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
		191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283
};

inline int rev(const int i,const int p) {
	return i ? p - i : i;
}

double hal(const int b, int j) {
	const int p = primes[b];
	double h = 0.0, f = 1.0 / (double) p, fct = f;
	while (j > 0) {
		h += rev(j % p, p) * fct;
		j /= p;
		fct *= f;
	}
	return h;
}

struct Vec {
	double x, y, z; // vector: position, also color (r,g,b)
	Vec(double x_ = 0, double y_ = 0, double z_ = 0) {
		x = x_;
		y = y_;
		z = z_;
	}

	inline Vec operator+(const Vec &b) const {
		return Vec(x + b.x, y + b.y, z + b.z);
	}

	inline Vec operator-(const Vec &b) const {
		return Vec(x - b.x, y - b.y, z - b.z);
	}

	inline Vec operator+(double b) const {
		return Vec(x + b, y + b, z + b);
	}

	inline Vec operator-(double b) const {
		return Vec(x - b, y - b, z - b);
	}

	inline Vec operator*(double b) const {
		return Vec(x * b, y * b, z * b);
	}

	inline Vec mul(const Vec &b) const {
		return Vec(x * b.x, y * b.y, z * b.z);
	}

	inline Vec norm() {
		return (*this) * (1.0 / sqrt(x * x + y * y + z * z));
	}

	inline double dot(const Vec &b) const {
		return x * b.x + y * b.y + z * b.z;
	}

	Vec operator%(Vec &b) {
		return Vec(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
};


struct AABB {
	Vec min, max; // axis aligned bounding box
	inline void fit(const Vec &p) {
		min.x = p.x < min.x ? p.x : min.x;
		min.y = p.y < min.y ? p.y : min.y;
		min.z = p.z < min.z ? p.z : min.z;
		max.x = p.x > max.x ? p.x : max.x;
		max.y = p.y > max.y ? p.y : max.y;
		max.z = p.z > max.z ? p.z : max.z;
	}

	inline void reset() {
		min = Vec(1e20, 1e20, 1e20);
		max = Vec(-1e20, -1e20, -1e20);
	}
};

struct HPoint {
	Vec f,pos,nrm,flux;
	double r2;
	unsigned int n; // n = N / ALPHA in the paper
	int pix;
};

unsigned int num_hash, pixel_index, num_photon;
double hash_s;
//List **hash_grid;
vector<HPoint*> *hash_grid;
vector<HPoint*> hitpoints;
AABB hpbbox;

// spatial hash function
inline unsigned int hash(const int ix, const int iy, const int iz) {
	return (unsigned int) ((ix * 73856093) ^ (iy * 19349663) ^ (iz * 83492791)) % num_hash;
}

void build_hash_grid(const int w, const int h) {
	// find the bounding box of all the measurement points
	hpbbox.reset();
	for (auto &hp : hitpoints) {
		hpbbox.fit(hp->pos);
	}

	// heuristic for initial radius
	Vec ssize = hpbbox.max - hpbbox.min;
	double irad = ((ssize.x + ssize.y + ssize.z) / 3.0) / ((w + h) / 2.0) * 2.0;

	// determine hash table size
	// we now find the bounding box of all the measurement points inflated by the initial radius
	hpbbox.reset();
	int vphoton = 0;
	for (auto &cur : hitpoints) {
		cur->r2 = irad * irad;
		cur->n = 0;
		cur->flux = Vec();
		++vphoton;
		hpbbox.fit(cur->pos - irad);
		hpbbox.fit(cur->pos + irad);
	}

	// make each grid cell two times larger than the initial radius
	hash_s = 1.0 / (irad * 2.0);
	num_hash = vphoton;

	// build the hash table
	hash_grid = new vector<HPoint *>[num_hash];
	for (unsigned int i = 0; i < num_hash; i++) hash_grid[i] = vector<HPoint *>();
	for (auto &hp : hitpoints) {
		Vec BMin = ((hp->pos - irad) - hpbbox.min) * hash_s;
		Vec BMax = ((hp->pos + irad) - hpbbox.min) * hash_s;
		for (int iz = abs(int(BMin.z)); iz <= abs(int(BMax.z)); iz++) {
			for (int iy = abs(int(BMin.y)); iy <= abs(int(BMax.y)); iy++) {
				for (int ix = abs(int(BMin.x)); ix <= abs(int(BMax.x)); ix++) {
					hash_grid[hash(ix, iy, iz)].push_back(hp);
				}
			}
		}
	}
}

struct Ray {
	Vec o, d;

	Ray() { };

	Ray(Vec o_, Vec d_) : o(o_), d(d_) { }
};

enum Refl_t {
	DIFF, SPEC, REFR
};  // material types, used in radiance()

struct Object {
	Refl_t refl;
	Vec color;
	Object (Refl_t refl, Vec c) : refl(refl), color(c) {}
	virtual double intersect(const Ray &) const = 0;
	virtual Vec normal(const Ray &, const Vec &) const = 0;
};

struct Sphere : Object {
	double rad;
	Vec p;

	Sphere(double r_, Vec p_, Vec c_, Refl_t refl) : Object(refl, c_), rad(r_), p(p_) {
	}

	double intersect(const Ray &r) const {
		// ray-sphere intersection returns distance
		Vec op = p - r.o;
		double t, b = op.dot(r.d), det = b * b - op.dot(op) + rad * rad;
		if (det < 0) {
			return 1e20;
		}
		else {
			det = sqrt(det);
		}
		return (t = b - det) > 1e-6 ? t : ((t = b + det) > 1e-6 ? t : 1e20);
	}

	Vec normal(const Ray &ray, const Vec &x) const {
		return (x - p).norm();
	}
};

struct Surface : Object {
	Vec n;
	Vec normal(const Ray &ray, const Vec &point) const {
		if (ray.d.dot(n) > 0) {
			return n * -1;
		}
		return n;
	}
	Surface(Vec c, Refl_t refl) : Object(refl, c) {}
};

double det(const Vec &x, const Vec &y, const Vec &z) {
	double d11 = x.x * (y.y * z.z - z.y * y.z);
	double d22 = y.x * (x.y * z.z - z.y * x.z);
	double d33 = z.x * (x.y * y.z - y.y * x.z);
	return d11 - d22 + d33;
}

struct Triangle : public Surface {
	Vec a, b, c, ba, ca;


	Triangle(Vec &a, Vec &b, Vec &c, Vec col, Refl_t t) : Surface(col, t), a(a), b(b), c(c), ba(a - b), ca(a - c) {
		n = (ba % ca).norm();
	}

	double intersect(const Ray &ray) const {
		double A = det(ba, ca, ray.d);
		if (A != 0) {
			Vec v = a - ray.o;
			double beta = det(v, ca, ray.d) / A;
			double gama = det(ba, v, ray.d) / A;
			if (beta > 0 && gama > 0 && beta + gama < 1) {
				double res = det(ba, ca, v) / A;
				if (res > 0.) {
					return res;
				} else {
					return 1e20;
				}
			}
		}
		return 1e20;
	}
};


vector<Object*> objs;

// tone mapping and gamma correction
int toInt(double x) {
	return int(pow(1 - exp(-x), 1 / 2.2) * 255 + .5);
}

// find the closet interection
inline bool intersect(const Ray &r,double &t,int &id) {
	double d, inf = 1e20;
	t = inf;
	for (size_t i = 0; i < objs.size(); ++i) {
		d = objs[i]->intersect(r);
		if (d < t) {
			t = d;
			id = i;
		}
	}
	return t < inf;
}

double rand11() {
	int sgn = rand() % 2 ? 1 : -1;
	double res = rand() / (double) RAND_MAX;
	return sgn * res;
}

// generate a photon ray from the point light source with QMC
void genp(Ray* pr, Vec* f, int i) {
	*f = Vec(2500, 2500, 2500) * (PI * 4.0); // flux
	double p = 2. * PI * hal(0, i), t = 2. * acos(sqrt(1. - hal(1, i)));
	double st = sin(t);
//	photon = Ray(Vec(randf()*20-10, randf()*10+15, 49.9), Vec(cos(p)*st, sin(p)*st, cos(t)));
	pr->d = Vec(cos(p) * st, sin(p) * st, cos(t));
	pr->o = Vec(rand11()*10, rand11()*5+20, 49.9);
}

void trace(const Ray &r,int dpt,bool m,const Vec &fl,const Vec &adj,int i) {
	double t;
	int id;

	dpt++;
	if (!intersect(r, t, id) || (dpt >= 20))return;

	int d3 = dpt * 3;
	const Object &obj = *objs[id];
	Vec x = r.o + r.d * t, n = obj.normal(r, x), f = obj.color;
	Vec nl = n.dot(r.d) < 0 ? n : n * -1;
	double p = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;

	if (obj.refl == DIFF) {
		// Lambertian

		// use QMC to sample the next direction
		double r1 = 2. * PI * hal(d3 - 1, i), r2 = hal(d3 + 0, i);
		double r2s = sqrt(r2);
		Vec w = nl, u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).norm();
		Vec v = w % u, d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();

		if (m) {
			// eye ray
			// store the measurment point
			HPoint *hp = new HPoint;
			hp->f = f.mul(adj);
			hp->pos = x;
			hp->nrm = n;
			hp->pix = pixel_index;
			hitpoints.push_back(hp);
//			printf("%d(%d): %f %f %f\n", (int)hitpoints.size(), id, x.x, x.y, x.z);
		}
		else {
			// photon ray
			// find neighboring measurement points and accumulate flux via progressive density estimation
			Vec hh = (x - hpbbox.min) * hash_s;
			int ix = abs(int(hh.x)), iy = abs(int(hh.y)), iz = abs(int(hh.z));
			// strictly speaking, we should use #pragma omp critical here.
			// it usually works without an artifact due to the fact that photons are
			// rarely accumulated to the same measurement points at the same time (especially with QMC).
			// it is also significantly faster.
			{
				for (auto &hitpoint : hash_grid[hash(ix, iy, iz)]) {
					Vec v = hitpoint->pos - x;
					// check normals to be closer than 90 degree (avoids some edge brightning)
					if ((hitpoint->nrm.dot(n) > 1e-3) && (v.dot(v) <= hitpoint->r2)) {
						// unlike N in the paper, hitpoint->n stores "N / ALPHA" to make it an integer value
						double g = (hitpoint->n * ALPHA + ALPHA) / (hitpoint->n * ALPHA + 1.0);
						hitpoint->r2 = hitpoint->r2 * g;
						hitpoint->n++;
						hitpoint->flux = (hitpoint->flux + hitpoint->f.mul(fl) * (1. / PI)) * g;
					}
				}
			}
			if (hal(d3 + 1, i) < p) trace(Ray(x, d), dpt, m, f.mul(fl) * (1. / p), adj, i);
		}

	} else if (obj.refl == SPEC) {
		// mirror
		trace(Ray(x, r.d - n * 2.0 * n.dot(r.d)), dpt, m, f.mul(fl), f.mul(adj), i);

	} else {
		// glass
		Ray lr(x, r.d - n * 2.0 * n.dot(r.d));
		bool into = (n.dot(nl) > 0.0);
		double nc = 1.0, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;

		// total internal reflection
		if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0) return trace(lr, dpt, m, fl, adj, i);

		Vec td = (r.d * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)))).norm();
		double a = nt - nc, b = nt + nc, R0 = a * a / (b * b), c = 1 - (into ? -ddn : td.dot(n));
		double Re = R0 + (1 - R0) * c * c * c * c * c, P = Re;
		Ray rr(x, td);
		Vec fa = f.mul(adj);
		if (m) {
			// eye ray (trace both rays)
			trace(lr, dpt, m, fl, fa * Re, i);
			trace(rr, dpt, m, fl, fa * (1.0 - Re), i);
		} else {
			// photon ray (pick one via Russian roulette)
			(hal(d3 - 1, i) < P) ? trace(lr, dpt, m, fl, fa, i) : trace(rr, dpt, m, fl, fa, i);
		}
	}
}

struct BMPIo {
	void out(int x, int num, ofstream& fout) {
		char buff[5];
		while (num--) {
			buff[0] = x & 255;
			x >>= 8;
			fout.write(buff, 1);
		}
	}

	BMPIo(string file_name, int width, int height, Vec *buffer) {
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
		for (int i = height - 1; i >= 0; --i)
		{
			for (int j = 0; j < width; ++j) {
				Vec *iter = buffer + i * width + j;
				int data = (toInt(iter->x) << 16) | (toInt(iter->y) << 8) | (toInt(iter->z));
				out(data, 3, fout);
			}
			out(0, tmp, fout);
		}
	}
};

void import_model(string file_name) {
	FILE *fin = fopen(file_name.c_str(), "r");
	char buffer[256];
	vector<Vec> points;
	while (fgets(buffer, sizeof buffer, fin)) {
		if (*buffer == 'v') {
			Vec tmp;
			sscanf(buffer + 1, "%lf %lf %lf", &tmp.x, &tmp.y, &tmp.z);
			tmp.x = tmp.x * 20 + 40;
			tmp.y = tmp.y * 20 + 50;
			tmp.z = tmp.z * 20 + 60;
			points.push_back(tmp);
		} else if (*buffer == 'f') {
			int a, b, c;
			sscanf(buffer + 1, "%d %d %d", &a, &b, &c);
			--a, --b, --c;
			objs.push_back(new Triangle(points[a], points[b], points[c], Vec(1, 1, 1) * .999, REFR));
		}
	}
	fclose(fin);

	// load walls
	double x_wall_min = -50;
	double x_wall_max = 50;
	double y_wall_min = -101;
	double y_wall_max = 50;
	double z_wall_min = -50;
	double z_wall_max = 50;

	Vec v000(x_wall_min,y_wall_min,z_wall_min);
	Vec v001(x_wall_min,y_wall_min,z_wall_max);
	Vec v010(x_wall_min,y_wall_max,z_wall_min);
	Vec v011(x_wall_min,y_wall_max,z_wall_max);
	Vec v100(x_wall_max,y_wall_min,z_wall_min);
	Vec v101(x_wall_max,y_wall_min,z_wall_max);
	Vec v110(x_wall_max,y_wall_max,z_wall_min);
	Vec v111(x_wall_max,y_wall_max,z_wall_max);

	// down
	objs.push_back(new Triangle(v010,v000,v110,Vec(0.75,0.75,0.75), DIFF));
	objs.push_back(new Triangle(v110,v000,v100,Vec(0.75,0.75,0.75), DIFF));

	// left
	objs.push_back(new Triangle(v001,v000,v011,Vec(0.10,0.10,0.90), DIFF));
	objs.push_back(new Triangle(v011,v000,v010,Vec(0.10,0.10,0.90), DIFF));
	// right
	objs.push_back(new Triangle(v101,v111,v100,Vec(0.50,0.50,0.25), DIFF));
	objs.push_back(new Triangle(v111,v110,v100,Vec(0.50,0.50,0.25), DIFF));
	// up
	objs.push_back(new Triangle(v011,v111,v001,Vec(0.75,0.75,0.75), DIFF));
	objs.push_back(new Triangle(v111,v101,v001,Vec(0.75,0.75,0.75), DIFF));
	// back
	objs.push_back(new Triangle(v011,v010,v111,Vec(0.75,0.75,0.75), DIFF));
	objs.push_back(new Triangle(v111,v010,v110,Vec(0.75,0.75,0.75), DIFF));

	// front
	objs.push_back(new Triangle(v001,v101,v000,Vec(0.25,0.25,0.25), DIFF));
	objs.push_back(new Triangle(v101,v100,v000,Vec(0.25,0.25,0.25), DIFF));

}

int main(int argc, char *argv[]) {
	// samps * 1000 photon paths will be traced
	int w = 512, h = 512, samps = (argc == 2) ? max(atoi(argv[1]) / 1000, 1) : 1000;

//	objs.push_back(new Sphere(1e5, Vec(1e5 + 1, 40.8, 81.6), Vec(.75, .25, .25), DIFF));//Left
//	objs.push_back(new Sphere(1e5, Vec(-1e5 + 99, 40.8, 81.6), Vec(.25, .25, .75), DIFF));//Right
//	objs.push_back(new Sphere(1e5, Vec(50, 40.8, 1e5), Vec(.75, .75, .75), DIFF));//Back
//	objs.push_back(new Sphere(1e5, Vec(50, 40.8, -1e5 + 170), Vec(), DIFF));//Front
//	objs.push_back(new Sphere(1e5, Vec(50, 1e5, 81.6), Vec(.75, .75, .75), DIFF));//Bottomm
//	objs.push_back(new Sphere(1e5, Vec(50, -1e5 + 81.6, 81.6), Vec(.75, .75, .75), DIFF));//Top
//	objs.push_back(new Sphere(16.5, Vec(27, 16.5, 47), Vec(1, 1, 1) * .999, SPEC));//Mirror
//	objs.push_back(new Sphere(16.5, Vec(73, 16.5, 88), Vec(1, 1, 1) * .999, REFR));//Glass
//	objs.push_back(new Sphere(8.5, Vec(50, 8.5, 60), Vec(1, 1, 1) * .999, DIFF));//Middle
	objs.push_back(new Sphere(12,  Vec(-15, 12 ,-38), Vec(1,1,1)*.99, SPEC));//Mirr
	objs.push_back(new Sphere(6,  Vec(5, 23, -44), Vec(1,1,1)*.99, DIFF));//Mirr
	objs.push_back(new Sphere(12,  Vec(21, 12, -38),Vec(1,1,1)*.99, REFR));//Mirr
	import_model("empty.obj");

	// trace eye rays and store measurement points
//	Ray cam(Vec(50, 48, 295.6), Vec(0, -0.042612, -1).norm());
//	Vec cx = Vec(w * .5135 / h), cy = (cx % cam.d).norm() * .5135, *c = new Vec[w * h], vw;
//	for (int y = 0; y < h; y++) {
//		fprintf(stderr, "\rHitPointPass %5.2f%%", 100.0 * y / (h - 1));
//		for (int x = 0; x < w; x++) {
//			pixel_index = x + y * w;
//			Vec d = cx * ((x + 0.5) / w - 0.5) + cy * (-(y + 0.5) / h + 0.5) + cam.d;
//			trace(Ray(cam.o + d * 140, d.norm()), 0, true, Vec(), Vec(1, 1, 1), 0);
//		}
//	}
//	fprintf(stderr, "\n");

	Ray cam(Vec(0, -100, 0), Vec(0, 1, 0).norm());
	Vec *c, vw;
	Vec *pre = NULL;
	for (int y = 0; y < h; y++) {
		fprintf(stderr, "\rHitPointPass %5.2f%%", 100.0 * y / (h - 1));
		for (int x = 0; x < w; x++) {
			pixel_index = x + y * w;
//			Vec a((x - w / 2.) / w);
//			Vec b(0, 0, (-y + h / 2.) / w);
//			Vec tmp(a % b);
//			printf("%d %d: %f\n", x, y, tmp.y);
//			assert(tmp.y >= 0);
//			Vec tmp((x - w / 2.) / w, 1, (-y + h / 2.) / w);
//			printf("%d %d: %f %f %f\n", x, y, tmp.x, tmp.y, tmp.z);
			trace(Ray(cam.o , Vec((x - w / 2. + rand11() * .5) / w, 1, (-y + h / 2. + rand11() * .5) / w).norm()), 0, true, Vec(), Vec(1, 1, 1), 0);
		}
	}
	fprintf(stderr, "\n");

	// build the hash table over the measurement points
	build_hash_grid(w, h);

	// trace photon rays with multi-threading
	num_photon = samps;
	vw = Vec(1, 1, 1);
	for (unsigned int i = 0; i < num_photon; i++) {
		double p = 100. * (i + 1) / num_photon;
		fprintf(stderr, "\rPhotonPass %5.2f%%", p);
		int m = 1000 * i;
		Ray r;
		Vec f;
		for (int j = 0; j < 1000; j++) {
			genp(&r, &f, m + j);
			trace(r, 0, 0 > 1, f, vw, m + j);
		}
		//printf("%d\n", (int) i % 10000);
		if ((int) (i) % 10000 == 9999) {
			static int cnt = 0;
			printf("%d: ", ++cnt);
			c = new Vec[w * h];
			for (auto &hp : hitpoints) {
				int idx = hp->pix;
				c[idx] = c[idx] + hp->flux * (1.0 / (PI * hp->r2 * (i + 1) * 1000.0));
			}
			char file_name[30];
			sprintf(file_name, "photons_%dkw.bmp", (i + 1) / 10000);
			BMPIo(file_name, w, h, c);

			double delta = 0;
			if (pre) {
				for (int j = 0; j < w * h; ++j) {
					Vec d = pre[j] - c[j];
					delta += d.dot(d);
				}
				delete[] pre;
			} else {
				for (int j = 0; j < w * h; ++j) {
					delta += c[j].dot(c[j]);
				}
			}
			sprintf(file_name, "delta_%dkw", (i + 1) / 10000);
			FILE *FOUT = fopen(file_name, "w");
			fprintf(FOUT, "%f", delta);
			fclose(FOUT);
			pre = c;
		}
	}

	// density estimation
	for (auto &hp : hitpoints) {
		int idx = hp->pix;
		c[idx] = c[idx] + hp->flux * (1.0 / (PI * hp->r2 * num_photon * 1000.0));
	}

	BMPIo("image.bmp", w, h, c);
	return 0;
}
