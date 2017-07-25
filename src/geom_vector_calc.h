#include <Rcpp.h>
#include <irrlicht.h>
#include <math.h>

using namespace Rcpp;

core::vector3df position_calc(DataFrame rcdf) {

  NumericVector x = rcdf["x"];
  NumericVector y = rcdf["y"];
  NumericVector z = rcdf["z"];

  core::vector3df pos(
    sum(x) / 4,
    sum(y) / 4,
    sum(z) / 4
  );

  Rcout << "position: " <<  pos.X << ", " << pos.Y << ", " << pos.Z << std::endl;

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

  Rcout << "scale: " <<  scale.X << ", " << scale.Y << ", " << scale.Z << std::endl;;

  return scale * 0.1;
}
