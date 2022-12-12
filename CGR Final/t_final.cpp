#include <fstream>
#include <cmath>

//Estruturas basicas de todos os "objetos" necessarios, como a palheta de cores, os raios e as esferas

struct Vec3 {
  double x,y,z;
  Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
  Vec3 operator + (const Vec3& v) const { return Vec3(x+v.x, y+v.y, z+v.z); }
  Vec3 operator - (const Vec3& v) const { return Vec3(x-v.x, y-v.y, z-v.z); }
  Vec3 operator * (double d) const { return Vec3(x*d, y*d, z*d); }
  Vec3 operator / (double d) const { return Vec3(x/d, y/d, z/d); }
  Vec3 normalize() const {
    double mg = sqrt(x*x + y*y + z*z);
    return Vec3(x/mg,y/mg,z/mg);
  }
};
inline double dot(const Vec3& a, const Vec3& b) {
  return (a.x*b.x + a.y*b.y + a.z*b.z);
}

struct Ray {
  Vec3 o,d;
  Ray(const Vec3& o, const Vec3& d) : o(o), d(d) {}
};

struct Sphere {
  Vec3 c;
  double r;
  Sphere(const Vec3& c, double r) : c(c), r(r) {}
  Vec3 getNormal(const Vec3& pi) const { return (pi - c) / r; }
  bool intersect(const Ray& ray, double &t) const {
    const Vec3 o = ray.o;
    const Vec3 d = ray.d;
    const Vec3 oc = o - c;
    const double b = 2 * dot(oc, d);
    const double c = dot(oc, oc) - r*r;
    double disc = b*b - 4 * c;
    if (disc < 1e-4) return false;
    disc = sqrt(disc);
    const double t0 = -b - disc;
    const double t1 = -b + disc;
    t = (t0 < t1) ? t0 : t1;
    return true;
  }
};

void clamp255(Vec3& col) {
  col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
  col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
  col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

int main() {
	
	
  //Criação da tela, definição das cores, criação das esferas coloridas e do ponto de luz
  
  const int H = 500;
  const int W = 500;

  const Vec3 white(255, 255, 255);
  const Vec3 black(0, 0, 0);
  const Vec3 red(255, 0, 0);
  const Vec3 green(0, 255, 0);
  const Vec3 blue(0, 0, 255);
  const Vec3 yellow(255, 255, 0);
  const Vec3 cyan(0, 255, 255);

  const Sphere sphere1(Vec3(W*0.2, H*0.2, 50), 50);
  const Sphere sphere2(Vec3(W*0.5, H*0.5, 50), 50);
  const Sphere sphere3(Vec3(W*0.8, H*0.8, 50), 50);
  const Sphere sphere4(Vec3(W*0.2, H*0.8, 50), 50);
  const Sphere sphere5(Vec3(W*0.8, H*0.2, 50), 50);

  
  const Sphere light(Vec3(10, 250, 100), 3);

  std::ofstream out("out.png");
  out << "P3\n" << W << ' ' << H << ' ' << "255\n";

  double t;
  Vec3 pix_col(black);

  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      
	  /*
	  Pinta tudo de preto, caso o raio atinja uma das esferas coloridas, um calculo
	  levando em consideração a fonte de luz e a superficie da esfera é realizado
	  para que seja definida a cor que deverá ser exibida nesse pixel.
	  */
	  
	  pix_col = black;

      const Ray ray(Vec3(x,y,0),Vec3(0,0,1));
      if (sphere1.intersect(ray, t)) {
        const Vec3 pi = ray.o + ray.d*t;
        const Vec3 L = light.c - pi;
        const Vec3 N = sphere1.getNormal(pi);
        const double dt = dot(L.normalize(), N.normalize());

        pix_col = (red + white*dt) * 0.5;
        clamp255(pix_col);
      }
      if (sphere2.intersect(ray, t)) {
        const Vec3 pi = ray.o + ray.d*t;
        const Vec3 L = light.c - pi;
        const Vec3 N = sphere2.getNormal(pi);
        const double dt = dot(L.normalize(), N.normalize());

        pix_col = (green + white*dt) * 0.5;
        clamp255(pix_col);
      }
      if (sphere3.intersect(ray, t)) {
        const Vec3 pi = ray.o + ray.d*t;
        const Vec3 L = light.c - pi;
        const Vec3 N = sphere3.getNormal(pi);
        const double dt = dot(L.normalize(), N.normalize());

        pix_col = (blue + white*dt) * 0.5;
        clamp255(pix_col);
      }
      if (sphere4.intersect(ray, t)) {
        const Vec3 pi = ray.o + ray.d*t;
        const Vec3 L = light.c - pi;
        const Vec3 N = sphere4.getNormal(pi);
        const double dt = dot(L.normalize(), N.normalize());

        pix_col = (yellow + white*dt) * 0.5;
        clamp255(pix_col);
      }
      if (sphere5.intersect(ray, t)) {
        const Vec3 pi = ray.o + ray.d*t;
        const Vec3 L = light.c - pi;
        const Vec3 N = sphere5.getNormal(pi);
        const double dt = dot(L.normalize(), N.normalize());

        pix_col = (cyan + white*dt) * 0.5;
        clamp255(pix_col);
      }
      
      out << (int)pix_col.x << ' '
          << (int)pix_col.y << ' '
          << (int)pix_col.z << '\n';
    }
  }
}