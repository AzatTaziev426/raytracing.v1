#ifndef RAY_HPP
#define RAY_HPP
#include <cmath>

namespace nray{
  template<typename T>
  class Vec3 {
    private:
      T x_pos,y_pos,z_pos;
    public:
    Vec3(T n):
      x_pos(n),y_pos(n),z_pos(n){}
    Vec3(T x, T y, T z) :
      x_pos(x), y_pos(y), z_pos(z){}

    T get_x() const {return x_pos;}
    T get_y() const {return y_pos;}
    T get_z() const {return z_pos;}

    void set_x(T x){ x_pos = x;}
    void set_y(T y){ y_pos = y;}
    void set_z(T z){ z_pos = z;}

    Vec3<T> operator + (const Vec3<T> &v) const {
      return Vec3(x_pos+v.x_pos, y_pos+v.y_pos, z_pos+v.z_pos);
    }
    Vec3<T> operator - (const Vec3<T> &v) const {
      return Vec3(x_pos-v.x_pos, y_pos-v.y_pos, z_pos-v.z_pos);
    }
    Vec3<T> operator * (T d) const {
      return Vec3<T>(x_pos*d, y_pos*d, z_pos*d);
     }
    Vec3<T> operator / (T d) const {
      return Vec3(x_pos/d, y_pos/d, z_pos/d);
    }
    Vec3<T> normalize() const {
      T magnitude = sqrt(x_pos*x_pos + y_pos*y_pos + z_pos*z_pos);
      return Vec3<T>(x_pos/magnitude,y_pos/magnitude,z_pos/magnitude);
    }
  };
template<typename T>
T dot(const Vec3<T> &a,const Vec3<T> &b){
    return (a.get_x()*b.get_x() + a.get_y()*b.get_y() + a.get_z() + b.get_z());
  }


template<typename T>
class Ray{
public:
  Vec3<T> o,d;
  Ray(const Vec3<T> &o, const Vec3<T> &d) : o(o),d(d) {}
};

template<typename T>
class Sphere{
public:
  Vec3<T> c;
  T r;
  Sphere(const Vec3<T> &c, T r) : c(c),r(r) {}
  Vec3<T> getNormal(const Vec3<T> &pi) const {return (pi - c) / r; }

  bool intersect(const Ray<T> &ray, T &t) const {
    const Vec3<T> o = ray.o;
    const Vec3<T> d = ray.d;
    const Vec3<T> oc = o - c;
    const T b = 2 * dot(oc,d);
    const T c = dot(oc,oc) - r*r;
    T disc = b*b - 4 * c;
    if(disc < 10e-4){ return false; }
    disc = sqrt(disc);
    const T t0 = -b - disc;
    const T t1 = -b + disc;
    if(t0 < t1){
      t = t0;
    } else { t = t1; }
    return true;
  }
};
}
typedef nray::Vec3<float> Vec3F;
typedef nray::Vec3<int> Vec3I;
typedef nray::Ray<float> Ray;
typedef nray::Sphere<float> Sphere;



#endif
