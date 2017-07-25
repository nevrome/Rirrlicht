#include "vector.h"

#define EPS 1e-10

// quaternion struct
typedef struct { union { struct { double x, y, z; }; v3 n; }; double w; } q4;

q4 q_crt(v3 n, double a) { 
  a*=0.5; 
  q4* res = new q4;
  res->n = v_mul(v_nor(n),sin(a));  
  res->w = cos(a);
  return (*res);
}

q4 q_nor(q4 a) { 
  double b = 1.0 / sqrt(v_sqr(a.n) + a.w * a.w);
  q4* res = new q4;
  res->n = v_mul(a.n, b);  
  res->w = a.w * b;
  return (*res);
}

double clamp(double a) { return (a > 1.0) ? 1.0 : ((a < -1.0) ? -1.0 : a);}
q4 q_btw(v3 a, v3 b) { 
  a = v_nor(a); b = v_nor(b);
  double d = v_dot(a, b);
  if (d >= 1.0) {
    q4* res = new q4;
    res->x = 0.0;  
    res->y = 0.0; 
    res->z = 0.0; 
    res->w = 1.0;
    return (*res);
  } else if (d <= -1.0) {
    v3 axis = v_crs((v3){1.0, 0.0, 0.0}, a);
    if (v_len(axis) < EPS) { axis = v_crs((v3){0.0, 1.0, 0.0}, a); }
    q4* res = new q4;
    res->n = v_nor(axis);  
    res->w = 0.0;
    return (*res);
  }
  double s = sqrt(2.0*(1+d)), i = 1.0 / s;
  
  q4* res = new q4;
  res->n = v_mul(v_crs(a,b), i);  
  res->w = 0.5 * s;
  return (q_nor(*res));
}
q4 q_inv(q4 a) { 
  q4* res = new q4;
  res->n = a.n;  
  res->w = -a.w;
  return (*res);
}
q4 q_mul(q4 a, q4 b) {
  return (q4) {
    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
    a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
    a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
  };
}
v3 q_rot(q4 r, v3 a) { 
  return (v3) { a.x*(r.x*r.x+r.w*r.w-r.y*r.y- r.z*r.z) + a.y*(2*r.x*r.y- 2*r.w*r.z) + a.z*(2*r.x*r.z+ 2*r.w*r.y),
                a.x*(2*r.w*r.z + 2*r.x*r.y) + a.y*(r.w*r.w - r.x*r.x+ r.y*r.y - r.z*r.z)+ a.z*(-2*r.w*r.x+ 2*r.y*r.z),
                a.x*(-2*r.w*r.y+ 2*r.x*r.z) + a.y*(2*r.w*r.x+ 2*r.y*r.z)+ a.z*(r.w*r.w - r.x*r.x- r.y*r.y+ r.z*r.z)
  };
}

void printq(q4 q) { printf("%f, %f, %f, %f", q.x, q.y, q.z, q.w); }