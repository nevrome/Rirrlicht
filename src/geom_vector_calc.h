#include <Rcpp.h>
#include <irrlicht.h>

using namespace Rcpp;

//' position
//' 
//' @description
//' huhu
//'  
//' @param corner_points huhu
//' 
core::vector3df position_calc(DataFrame corner_points) {
  
  NumericVector xras = corner_points["x"];
  NumericVector yras = corner_points["y"];
  NumericVector zras = corner_points["z"];
  
  core::vector3df pos(
    (xras(0) + xras(3)) / 2,
    (yras(0) + yras(3)) / 2,
    (zras(0) + zras(3)) / 2
  );
  
  return pos;  
}

//' normal
//' 
//' @description
//' huhu
//'  
//' @param corner_points huhu
//' 
core::vector3df normal_calc(DataFrame corner_points) {
  
  NumericVector xras = corner_points["x"];
  NumericVector yras = corner_points["y"];
  NumericVector zras = corner_points["z"];
  
  NumericVector vertex1 = NumericVector::create(
    xras(0), yras(0), zras(0)
  );
  
  NumericVector vertex2 = NumericVector::create(
    xras(1), yras(1), zras(1)
  );
  
  NumericVector vertex3 = NumericVector::create(
    xras(2), yras(2), zras(2)
  );
  
  NumericVector v1 = vertex2 - vertex1;
  NumericVector v2 = vertex3 - vertex1;
  
  core::vector3df norm(
    v1(1)*v2(2) - v2(1)*v1(2),
    v1(2)*v2(0) - v2(2)*v1(0),
    v1(0)*v2(1) - v2(0)*v1(1)
  );
  
  return norm;  
}