#include <cstdio>
#include <cmath>
#include <vector>

using namespace std;

const double oo = 1e99;

inline double min(double a, double b) {
	return a < b ? a : b;
}
 
class Vector3
{
public:

	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3(const Vector3 &other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	double operator*(const Vector3 &b) const {
		return x * b.x + y * b.y + z * b.z;
	}

	Vector3 operator*(double k) const {
		Vector3 r(x * k, y * k, z * k);
		return r;
	}

	Vector3 operator+(const Vector3 &b) const {
		Vector3 r(x + b.x, y + b.y, z + b.z);
		return r;
	}

	Vector3 operator+(double d) const {
		Vector3 r(x + d, y + d, z + d);
		return r;
	}

	Vector3 operator-(const Vector3 &b) const {
		Vector3 r(x - b.x, y - b.y, z - b.z);
		return r;
	}

	Vector3 operator+=(const Vector3 &b) {
		x += b.x;
		y += b.y;
		z += b.z;
		return *this;
	}

	Vector3 mul(const Vector3 &b) {
		Vector3 r(x * b.x, y * b.y, z * b.z);
		return r;
	}

	Vector3 cross(const Vector3 &b) {
		Vector3 r;
		r.x = y * b.z - z * b.y;
		r.y = z * b.x - x * b.z;
		r.z = x * b.y - y * b.x;
		return r;
	}

	const Vector3& normalize() {
		double length = sqrt(x * x + y * y + z * z);
		x = x / length;
		y = y / length;
		z = z / length;
		return *this;
	}

	const Vector3& set(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
		return *this;
	}

public:

	double x;
	double y;
	double z;
};
class Object
{
public:

	virtual double hit(Ray &ray) = 0;
	virtual Vector3 normal(Ray &ray, Vector3 &point) = 0;

public:

	struct Material
	{
		Vector3 ambient;
		Vector3 diffuse;
		Vector3 specular;
		double reflection;
		double n;
	} material;
};

class Sphere : public Object
{
public:

	Sphere(double x, double y, double z, double r) {
		center = Vector3(x, y, z);
		radius = r;
	}

	double hit(Ray &ray) {
		Vector3 v = ray.origin - center;

		double dv = ray.direction * v;
		double delta = dv * dv - v * v + radius * radius;

		return delta > 0 ? -dv - sqrt(delta) : oo;
	}

	Vector3 normal(Ray &ray, Vector3 &point) {
		return (point - center).normalize();
	}

public:

	Vector3 center;

	double radius;
};

class Matrix33
{
public:

	static double det(const Vector3 &x, const Vector3 &y, const Vector3 &z) {
		double d11 = x.x * (y.y * z.z - z.y * y.z);
		double d22 = y.x * (x.y * z.z - z.y * x.z);
		double d33 = z.x * (x.y * y.z - y.y * x.z);
		return d11 - d22 + d33;
	}
};

class Surface : public Object
{
public:

	Vector3 normal(Ray &ray, Vector3 &point) {
		if (ray.direction * n > 0) {
			return n * -1;
		}

		return n;
	}

public:

	Vector3 n;
};

class Triangle : public Surface
{
public:

	Triangle() {

	}

	Triangle(Vector3 &a, Vector3 &b, Vector3 &c) {
		this->a = a;
		this->b = b;
		this->c = c;
		
		ba = a - b;
		ca = a - c;

		n = ba.cross(ca).normalize();
	}

	double hit(Ray &ray) {
		double A = Matrix33::det(ba, ca, ray.direction);

		if (A != 0) {
			Vector3 v = a - ray.origin;
			double beta = Matrix33::det(v, ca, ray.direction) / A;
			double gama = Matrix33::det(ba, v, ray.direction) / A;

			if (beta > 0 && gama > 0 && beta + gama < 1) {
				return Matrix33::det(ba, ca, v) / A;
			}
		}

		return oo;
	}

public:

	Vector3 a;
	Vector3 b;
	Vector3 c;

	Vector3 ba;
	Vector3 ca;
};

class Rectangle : public Surface
{
public:

	Rectangle() {

	}

	Rectangle(Vector3 &start, Vector3 &d1, Vector3 &d2) {
		this->start = start;
		this->d1 = d1;
		this->d2 = d2;

		n = d1.cross(d2).normalize();
	}

	double hit(Ray &ray) {
		double A = Matrix33::det(d1, d2, ray.direction);

		if (A != 0) {
			Vector3 v = ray.origin - start;
			double beta = Matrix33::det(v, d2, ray.direction) / A;
			double gama = Matrix33::det(d1, v, ray.direction) / A;

			if (beta >= 0 && gama >= 0 && beta <= 1 && gama <= 1) {
				return -Matrix33::det(d1, d2, v) / A;
			}
		}

		return oo;
	}

public:

	Vector3 start;
	Vector3 d1;
	Vector3 d2;
};

class Circle : public Surface
{
public:

	Circle(Vector3 &center, Vector3 &normal, double radius) {
		this->center = center;
		this->n = normal.normalize();
		this->radius = radius;
	}

	double hit(Ray &ray) {
		double a = n * ray.direction;
		if (a != 0) {
			double t = -(n * (ray.origin - center) / a);
			Vector3 point = ray.point(t);
			double dis_square = (point - center) * (point - center);
			if (dis_square <= radius * radius) {
				return t;
			}
		}

		return oo;
	}

public:

	Vector3 center;
	double radius;
};

class Cylinder : public Object
{
public:

	Cylinder()
		:Object() {

	}

	Cylinder(Vector3 &center, Vector3 &normal, double radius)
		:Object(), center(center), n(normal), radius(radius) {
		unitNormal = normal.normalize();
	}

	double hit(Ray &ray) {
		Vector3 v1 = ray.direction - unitNormal * (ray.direction * unitNormal);
		Vector3 v = ray.origin - center;
		Vector3 v2 = v - unitNormal * (v * unitNormal);

		double a = v1 * v1;
		double b = 2 * (v1 * v2);
		double c = v2 * v2 - radius * radius;

		double d = b * b - 4 * a * c;

		if (d >= 0) {
			double t = (-b - sqrt(d)) / (2 * a);
			Vector3 point = ray.point(t);
			double dot = (point - center) * unitNormal;
			if (dot >= 0) {
				Vector3 projection = unitNormal * dot;
				double d1 = projection * projection;
				double d2 = n * n;
				if (d1 <= d2) {
					return t;
				}
			}

			t = (-b + sqrt(d)) / (2 * a);
			point = ray.point(t);
			dot = (point - center) * unitNormal;
			if (dot >= 0) {
				Vector3 projection = unitNormal * dot;
				double d1 = projection * projection;
				double d2 = n * n;
				if (d1 <= d2) {
					return t;
				}
			}
		}

		return oo;
	}

	Vector3 normal(Ray &ray, Vector3 &point) {
		Vector3 v = point - center;
		Vector3 _n =  (v - unitNormal * (v * unitNormal)).normalize();
		if (ray.direction * _n > 0) {
			_n = _n * -1;
		}
		return _n;
	}

public:

	Vector3 center;
	Vector3 n;
	Vector3 unitNormal;

	double radius;
};

class Box : public Object
{
public:

	Box(Vector3 &start, Vector3 &d1, Vector3 &d2, Vector3 &d3) {
		face[0] = Rectangle(start, d1, d2);
		face[1] = Rectangle(start + d3, d1, d2);
		face[2] = Rectangle(start, d2, d3);
		face[3] = Rectangle(start + d1, d2, d3);
		face[4] = Rectangle(start, d1, d3);
		face[5] = Rectangle(start + d2, d1, d3);
	}

	double hit(Ray &ray) {
		double close_t = oo;
		for (int i = 0; i < 6; ++i) {
			double t = face[i].hit(ray);
			if (t < close_t) {
				close_t = t;
			}
		}
		return close_t;
	}

	Vector3 normal(Ray &ray, Vector3 &point) {
		double p_min = oo;
		int inter_i = 0;
		for (int i = 0; i < 6; ++i) {
			double p = abs((point - face[i].start) * face[i].n);
			if (p < p_min) {
				p_min = p;
				inter_i = i;
			}
		}
		return face[inter_i].normal(ray, point);
	}

public:

	Rectangle face[6];
};

class Ray
{
public:
	Vector3 point(double t) {
		return origin + direction * t;
	}

public:

	Vector3 origin;
	Vector3 direction;
};


struct PointLight
{
	Vector3 position;
	Vector3 intensity;
};

class Camera
{
public:

	Camera() {
		position.set(0, 300, -500);
		front = Vector3(0, 0, 0) - position;
		front.normalize();
		right.set(1, 0, 0);
		right.normalize();
		up = front.cross(right).normalize();

		half_x = 300;
		half_y = 200;

		scale = 16.0;
	}

	Ray cast(double screen_x, double screen_y) {
		Ray ray;
		ray.origin = position;
		ray.direction = (right * screen_x + up * screen_y - ray.origin).normalize();
		return ray;
	}

	Vector3 position;
	Vector3 up;
	Vector3 front;
	Vector3 right;
	Vector3 start;

	int half_x;
	int half_y;

	double scale;
};

class Engine
{
public:

	Engine() {
		max_depth = 5;
	}

	void render() {
		camera.half_x *= camera.scale;
		camera.half_y *= camera.scale;


		for (int y = -camera.half_y; y <= camera.half_y; ++y) {
			uchar *p = screen.ptr<uchar>(camera.half_y - y);
			for (int x = -camera.half_x; x <= camera.half_x; ++x) {
				Ray ray = camera.cast(x / (2 * camera.scale), y / (2 * camera.scale));
				Vector3 color = tracing(ray, 0);

				int i = (x + camera.half_x) * 3;
				p[i++] = min(color.z * 255, 255);
				p[i++] = min(color.y * 255, 255);
				p[i++] = min(color.x * 255, 255);

			}
		}

	}

	Vector3 tracing(Ray &ray, int depth) {
		double close_t = oo;
		Object *close_o = NULL;

		for (auto obj : objs) {
			double t = obj->hit(ray);
			if (1e-9 < t && t < close_t) {
				close_t = t;
				close_o = obj;
			}
		}

		if (close_o != NULL) {
			Vector3 point = ray.point(close_t);
			Vector3 normal = close_o->normal(ray, point);
			return shade(close_o, ray, point, normal, depth);
		}

		return Vector3(0, 0, 0);
	}

	Vector3 shade(Object *obj, Ray &ray, Vector3 &point, Vector3 &normal, int depth) {
		Vector3 color = ambient.mul(obj->material.ambient);
		for (auto pl : lights) {
			Ray sRay;
			sRay.origin = point;
			sRay.direction = (pl.position - point).normalize();
			
			double cos_theta = normal * sRay.direction;
			if (cos_theta > 0) {
				double limit_t = 0;
				if (pl.position.x != point.x) {
					limit_t = (pl.position.x - point.x) / sRay.direction.x;
				}
				else if (pl.position.y != point.y) {
					limit_t = (pl.position.y - point.y) / sRay.direction.y;
				}
				else {
					limit_t = (pl.position.z - point.z) / sRay.direction.z;
				}
				bool blocked = false;
				for (auto other_obj : objs) {
					if (other_obj != obj) {
						double t = other_obj->hit(sRay);
						if (1e-9 < t && t < limit_t) {
							blocked = true;
							break;
						}
					}
				}
				if (!blocked) {
					double dis_square = (pl.position - point) * (pl.position - point);
					double dis = sqrt(dis_square);
					double f = 1.0 / (0.00001 * dis_square);
					if (f > 1) {
						f = 1.0;
					}
					color += pl.intensity.mul(obj->material.diffuse * cos_theta + obj->material.specular * pow(cos_theta, obj->material.n));
				}
			}
		}
		if (depth < max_depth) {
			if (obj->material.reflection != 0) {
				Ray rRay;
				rRay.origin = point;
				rRay.direction = ray.direction - normal * (ray.direction * normal * 2);
				color += tracing(rRay, depth + 1) * obj->material.reflection;
			}
		}
		return color;
	}

	void import(const char *scenefile) {
		FILE *fp = fopen(scenefile, "rb");
		char tag[64];
		fscanf(fp, "%s", tag);

		vector<Object::Material> mtls;
		do {
			Object::Material mtl;
			fscanf(fp, "\tambient %lf %lf %lf", &mtl.ambient.x, &mtl.ambient.y, &mtl.ambient.z);
			fscanf(fp, "\tdiffuse %lf %lf %lf", &mtl.diffuse.x, &mtl.diffuse.y, &mtl.diffuse.z);
			fscanf(fp, "\tspecular %lf %lf %lf", &mtl.specular.x, &mtl.specular.y, &mtl.specular.z);
			fscanf(fp, "\tn %lf", &mtl.n);
			fscanf(fp, "\treflection %lf", &mtl.reflection);
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
				Vector3 s, d1, d2;
				fscanf(fp, "\tstart %lf %lf %lf", &s.x, &s.y, &s.z);
				fscanf(fp, "\td1 %lf %lf %lf", &d1.x, &d1.y, &d1.z);
				fscanf(fp, "\td2 %lf %lf %lf", &d2.x, &d2.y, &d2.z);
				obj = new Rectangle(s, d1, d2);
			}
			else if (strcmp(tag, "Box") == 0) {
				Vector3 s, d1, d2, d3;
				fscanf(fp, "\tstart %lf %lf %lf", &s.x, &s.y, &s.z);
				fscanf(fp, "\td1 %lf %lf %lf", &d1.x, &d1.y, &d1.z);
				fscanf(fp, "\td2 %lf %lf %lf", &d2.x, &d2.y, &d2.z);
				fscanf(fp, "\td3 %lf %lf %lf", &d3.x, &d3.y, &d3.z);
				obj = new Box(s, d1, d2, d3);
			}
			else if (strcmp(tag, "Cylinder") == 0) {
				Vector3 c, n;
				double r;
				fscanf(fp, "\tcenter %lf %lf %lf", &c.x, &c.y, &c.z);
				fscanf(fp, "\tnormal %lf %lf %lf", &n.x, &n.y, &n.z);
				fscanf(fp, "\tradius %lf", &r);
				obj = new Cylinder(c, n, r);
			}

			int mtl_index;
			fscanf(fp, "\tmaterial %d", &mtl_index);
			obj->material = mtls[mtl_index];

			if (ignorance) {
				delete obj;
			}
			else {
				objs.push_back(obj);
			}
			fscanf(fp, "%s", tag);
		}

		fscanf(fp, "\tAmbient %lf %lf %lf", &ambient.x, &ambient.y, &ambient.z);

		while (fscanf(fp, "%s", tag) != EOF) {
			bool ignorance = tag[0] == '#';
			if (ignorance) {
				int len = strlen(tag) - 1;
				for (int i = 0; i < len; ++i) {
					tag[i] = tag[+1];
				}
				tag[len] = 0;
			}

			PointLight pl;
			fscanf(fp, "\tposition %lf %lf %lf", &pl.position.x, &pl.position.y, &pl.position.z);
			fscanf(fp, "\tintensity %lf %lf %lf", &pl.intensity.x, &pl.intensity.y, &pl.intensity.z);

			if (!ignorance) {
				lights.push_back(pl);
			}
		}

		fclose(fp);
	}

public:

	vector<Object*> objs;

	Vector3 ambient;
	vector<PointLight> lights;

	Camera camera;

	int max_depth;
} engine;

void trace(const Ray &r,int depth,bool m,const Vector3 &fl,const Vector3 &adj,int i) {
	if (++depth >= 20) {
		return ;
	}
	int id = -1;
	double dis;
	vector<Object*> objs = engine.objs;
	for (size_t i = 0; i < objs.size(); ++i) {
		double t = objs[i]->hit(r);
		if (id == -1 || t < oo) {
			dis = t;
			id = i;
		}
	}
	if (id == -1) {
		return ;
	}

	Object *obj = objs[id];
	Vector3 x = r.origin + r.direction * dis;
	Vector3 n = obj->normal(r, x);
	Vector3 f = obj->material.diffuse;
	Vector3 nl = n.dot(r.direction) < 0 ? n : n * -1;
	double p = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;

	if (obj.refl == DIFF) {
		// Lambertian

		// use QMC to sample the next direction
		double r1=2.*PI*hal(d3-1,i),r2=hal(d3+0,i);
		double r2s=sqrt(r2);
		Vec w=nl,u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm();
		Vec v=w%u, d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();

		if (m) {
			// eye ray
			// store the measurment point
			HPoint* hp=new HPoint; 
			hp->f=f.mul(adj); 
			hp->pos=x;
			hp->nrm=n; 
			hp->pix = pixel_index; 
			hitpoints = ListAdd(hp, hitpoints);
		} 
		else 
		{
			// photon ray
			// find neighboring measurement points and accumulate flux via progressive density estimation
			Vec hh = (x-hpbbox.min) * hash_s;
			int ix = abs(int(hh.x)), iy = abs(int(hh.y)), iz = abs(int(hh.z));
			// strictly speaking, we should use #pragma omp critical here.
			// it usually works without an artifact due to the fact that photons are 
			// rarely accumulated to the same measurement points at the same time (especially with QMC).
			// it is also significantly faster.
			{
				List* hp = hash_grid[hash(ix, iy, iz)]; 
				while (hp != NULL) {
					HPoint *hitpoint = hp->id; 
					hp = hp->next; 
					Vec v = hitpoint->pos - x;
					// check normals to be closer than 90 degree (avoids some edge brightning)
					if ((hitpoint->nrm.dot(n) > 1e-3) && (v.dot(v) <= hitpoint->r2)) {
						// unlike N in the paper, hitpoint->n stores "N / ALPHA" to make it an integer value
						double g = (hitpoint->n*ALPHA+ALPHA) / (hitpoint->n*ALPHA+1.0);
						hitpoint->r2=hitpoint->r2*g; 
						hitpoint->n++;
						hitpoint->flux=(hitpoint->flux+hitpoint->f.mul(fl)*(1./PI))*g;
					}
				}
			}
			if (hal(d3+1,i)<p) trace(Ray(x,d),dpt,m,f.mul(fl)*(1./p),adj,i);
		}

	} else if (obj.refl == SPEC) {
		// mirror
		trace(Ray(x, r.d-n*2.0*n.dot(r.d)), dpt, m, f.mul(fl), f.mul(adj),i);

	} else {
		// glass
		Ray lr(x,r.d-n*2.0*n.dot(r.d)); 
		bool into = (n.dot(nl)>0.0);
		double nc = 1.0, nt=1.5, nnt = into?nc/nt:nt/nc, ddn = r.d.dot(nl), cos2t;

		// total internal reflection
		if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0) return trace(lr,dpt,m,fl,adj,i);

		Vec td = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
		double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:td.dot(n));
		double Re=R0+(1-R0)*c*c*c*c*c,P=Re;Ray rr(x,td);Vec fa=f.mul(adj);
		if (m) {
			// eye ray (trace both rays)
			trace(lr,dpt,m,fl,fa*Re,i);
			trace(rr,dpt,m,fl,fa*(1.0-Re),i);
		} else {
			// photon ray (pick one via Russian roulette)
			(hal(d3-1,i)<P)?trace(lr,dpt,m,fl,fa,i):trace(rr,dpt,m,fl,fa,i);
		}
	}
}
int main() {

	engine.import("scene.txt");
	engine.render();

	return 0;
}
