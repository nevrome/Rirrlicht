#include <Rcpp.h>

using namespace Rcpp;

//' normal
//' 
//' @description
//' huhu
//'  
//' @param corner_points huhu
//' 
//' @export
// [[Rcpp::export]]
NumericVector normal_calc(DataFrame corner_points) {
  
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
  
  NumericVector normal = NumericVector::create(
    v1(1)*v2(2) - v2(1)*v1(2),
    v1(2)*v2(0) - v2(2)*v1(0),
    v1(0)*v2(1) - v2(0)*v1(1)
  );
  
  return normal;  
}