#include <Rcpp.h>
#include <cstdlib>
#include <unistd.h>
#include <irrlicht.h>
#include "rect.h"

using namespace Rcpp;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

core::vector3df position_calc(DataFrame rcdf) {

  NumericVector x = rcdf["x"];
  NumericVector y = rcdf["y"];
  NumericVector z = rcdf["z"];

  core::vector3df pos(
    sum(x) / 4,
    sum(y) / 4,
    sum(z) / 4
  );

  Rcout << "Image position: " <<  pos.X << ", " << pos.Y << ", " << pos.Z << std::endl;

  return pos;
}

core::vector3df scale_calc(DataFrame rcdf) {

  NumericVector x = rcdf["x"];
  NumericVector y = rcdf["y"];
  NumericVector z = rcdf["z"];

  core::vector3df lu(x(0), y(0), z(0));
  core::vector3df ru(x(1), y(1), z(1));
  core::vector3df lo(x(3), y(3), z(3));

  core::vector3df scale(
    lu.getDistanceFrom(lo),
    lu.getDistanceFrom(ru),
    0
  );

  Rcout << "Image scale: " <<  scale.X << ", " << scale.Y << ", " << scale.Z << std::endl;;

  return scale * 0.1;
}

vector3df rotation_calc(DataFrame rcdf) {
  // transform DataFrame to r12
  NumericVector x = rcdf["x"];
  NumericVector y = rcdf["y"];
  NumericVector z = rcdf["z"];
  r12 rcdf2 = { 
    (v3) {x[0], y[0], z[0]},
    (v3) {x[1], y[1], z[1]},
    (v3) {x[2], y[2], z[2]},
    (v3) {x[3], y[3], z[3]}
  };
  // check if r12 is valid (correct point order)
  if (!r_valid(rcdf2)) { Rcpp::Rcout << "Corner coordinates of image are not valid. Rotation may be wrong." << std::endl ; }
  // subtract center offset
  rcdf2 = r_sub(rcdf2, r_ctr(rcdf2));
  // p quaternion (between normals)
  q4 p = q_btw((v3) { 0.0, 0.0, 1.0 }, r_normal(rcdf2));
  // mid-point calculations
  v3 mab = (v3) { 0.0, 1.0, 0.0 };
  v3 u = q_rot(p, mab);
  v3 mde = v_mul(v_add(rcdf2.p[0],rcdf2.p[3]), 0.5);
  // q quaternion
  q4 q = q_btw(mab, mde);
  // multiplication
  q4 r = q_mul(p, q);
  // transform quaternion to degrees
  quaternion f(r.x, r.y, r.z, r.w);
  vector3df euler;
  f.toEuler(euler);
  vector3df degrees(
      euler.X * (180.0 / M_PI),
      euler.Y * (180.0 / M_PI),
      euler.Z * (180.0 / M_PI)
  );
  
  Rcout << "Image rotation degrees: " <<  degrees.X << ", " << degrees.Y << ", " << degrees.Z << std::endl;
  
  return degrees; // i swapped the order on this operation
}