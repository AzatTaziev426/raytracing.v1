#include "ray_header.hpp"
#include <fstream>

void clamp255(Vec3F &col){
  float x,y,z;
   x = (col.get_x()  > 255) ? 255 : (col.get_x() < 0) ? 0 : col.get_x();
   y = (col.get_y()  > 255) ? 255 : (col.get_y() < 0) ? 0 : col.get_y();
   z = (col.get_z()  > 255) ? 255 : (col.get_z() < 0) ? 0 : col.get_z() ;
   col.set_x(x);
   col.set_y(y);
   col.set_z(z);
}




int main(){

  const int H = 1080;
  const int W = 1980;

  const Vec3F white(255, 255,255);
  const Vec3F teal(50, 50, 50);
  const Vec3F green(0, 128, 0);
  const Vec3F indigo(75, 0, 130);
  const Vec3F gold(255,215,0);

  const Sphere sphere1(Vec3F(W*0.3, H*0.5, 150), 250);
  const Sphere sphere2(Vec3F(W*0.6, H*0.5, 150), 150);
  const Sphere light(Vec3F(0,0,0), 0);

  std::ofstream out("out.ppm");
  out << "P3\n" << W << ' ' << H << ' ' << "255\n";

  float t;
  Vec3F pix_col(teal);

  for (int y = 0; y < H; ++y) {
    for (int x = 0; x < W; ++x) {
      pix_col = teal;

      const Ray ray(Vec3F(x,y,0),Vec3F(0,0,1));
      if(sphere1.intersect(ray, t)){
        const Vec3F pi = ray.o + ray.d*t;
        const Vec3F L = light.c - pi;
        const Vec3F N = sphere1.getNormal(pi);
        const float dt = nray::dot(L.normalize(), N.normalize());

        pix_col = (indigo + white*dt) * 0.5;
        clamp255(pix_col);
      }

      if(sphere2.intersect(ray, t)){
        const Vec3F pi = ray.o + ray.d*t;
        const Vec3F L = light.c - pi;
        const Vec3F N = sphere2.getNormal(pi);
        const float dt = nray::dot(L.normalize(), N.normalize());

        pix_col = (gold + white*dt) * 0.3;
        clamp255(pix_col);
      }
      out << (int)pix_col.get_x() << ' '
          << (int)pix_col.get_y() << ' '
          << (int)pix_col.get_z() << '\n';
    }
  }
}
