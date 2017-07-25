#include "quaternion.h"

// input r12angle struct (anti-clockwise)
typedef struct { v3 p[4]; } r12;

int r_valid(r12 r) {
  v3 e[4] = { v_sub(r.p[1], r.p[0]), v_sub(r.p[2], r.p[1]), 
              v_sub(r.p[3], r.p[2]), v_sub(r.p[0], r.p[3]) };
  if (fabs(v_len(e[0])-v_len(e[2])) > EPS || fabs(v_len(e[1])-v_len(e[3])) > EPS)
    return 0;
  if (fabs(v_dot(e[0],e[1])) > EPS || fabs(v_dot(e[1],e[2])) > EPS ||
      fabs(v_dot(e[2],e[3])) > EPS || fabs(v_dot(e[3],e[0])) > EPS)
    return 0;
  v3 n[4] = { v_nor(v_crs(e[0],e[1])), v_nor(v_crs(e[1],e[2])),
              v_nor(v_crs(e[2],e[3])), v_nor(v_crs(e[3],e[0])) };
  if (v_dot(n[0],n[1]) < 1 - EPS || v_dot(n[1],n[2]) < 1 - EPS ||
      v_dot(n[2],n[3]) < 1 - EPS || v_dot(n[3],n[0]) < 1 - EPS)
    return 0;
  return 1;
}
v3 r_normal(r12 r) { return v_nor(v_crs(v_sub(r.p[1],r.p[0]),v_sub(r.p[3],r.p[0]))); }
double r_width(r12 r) { return v_len(v_sub(r.p[3],r.p[0])); }
double r_height(r12 r) { return v_len(v_sub(r.p[1],r.p[0])); }
r12 r_get(q4 r, double w, double h) {
  w *= 0.5; h *= 0.5;
  return (r12) { q_rot(r, (v3) { -w, h, 0.0 }),
                  q_rot(r, (v3) { -w, -h, 0.0 }),
                  q_rot(r, (v3) { w, -h, 0.0 }),
                  q_rot(r, (v3) { w, h, 0.0 })
  };
}
v3 r_ctr(r12 r) { return v_mul(v_add(r.p[0],v_add(r.p[1],v_add(r.p[2],r.p[3]))),0.25); }
r12 r_add(r12 r, v3 a) { return (r12) {v_add(r.p[0],a),v_add(r.p[1],a),v_add(r.p[2],a),v_add(r.p[3],a)}; }
r12 r_sub(r12 r, v3 a) { return (r12) {v_sub(r.p[0],a),v_sub(r.p[1],a),v_sub(r.p[2],a),v_sub(r.p[3],a)}; }


// compute the rotation 
q4 r_compute(r12 rcdf) {
  if (!r_valid(rcdf)) { return (q4) { 0.0, 0.0, 0.0, 0.0 }; }
  // subtract center offset
  rcdf = r_sub(rcdf, r_ctr(rcdf));
  // p quaternion (between normals)
  q4 p = q_btw((v3) { 0.0, 0.0, 1.0 }, r_normal(rcdf));
  // mid-point calculations
  v3 mab = (v3) { 0.0, 1.0, 0.0 };
  v3 u = q_rot(p, mab);
  v3 mde = v_mul(v_add(rcdf.p[0],rcdf.p[3]), 0.5);
  // q quaternion
  q4 q = q_btw(mab, mde);
  return q_mul(p, q); // i swapped the order on this operation
}