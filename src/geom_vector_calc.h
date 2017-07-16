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
  
  NumericVector x = corner_points["x"];
  NumericVector y = corner_points["y"];
  NumericVector z = corner_points["z"];
  
  core::vector3df pos(
    sum(x) / 4,
    sum(y) / 4,
    sum(z) / 4
  );
  
  Rcout << "position: " <<  pos.X << ", " << pos.Y << ", " << pos.Z << std::endl;;
  
  return pos;  
}

core::vector3df scale_calc(DataFrame corner_points) {
  
  NumericVector x = corner_points["x"];
  NumericVector y = corner_points["y"];
  NumericVector z = corner_points["z"];
  
  core::vector3df lu(x(0), y(0), z(0));
  core::vector3df ru(x(1), y(1), z(1));
  core::vector3df lo(x(3), y(3), z(3));
  
  core::vector3df scale(
    lu.getDistanceFrom(ru),
    lu.getDistanceFrom(lo),  
    0
  );
  
  Rcout << "scale: " <<  scale.X << ", " << scale.Y << ", " << scale.Z << std::endl;;
  
  return scale * 0.1;  
}

//' normal
//' 
//' @description
//' huhu
//'  
//' @param corner_points huhu
//' 
core::vector3df normal_calc(DataFrame corner_points) {
  
  NumericVector x = corner_points["x"];
  NumericVector y = corner_points["y"];
  NumericVector z = corner_points["z"];
  
  NumericVector vertex1 = NumericVector::create(
    x(0), y(0), z(0)
  );
  
  NumericVector vertex2 = NumericVector::create(
    x(1), y(1), z(1)
  );
  
  NumericVector vertex3 = NumericVector::create(
    x(2), y(2), z(2)
  );
  
  NumericVector v1 = vertex2 - vertex1;
  NumericVector v2 = vertex3 - vertex1;
  
  core::vector3df norm(
    v1(1)*v2(2) - v2(1)*v1(2),
    v1(2)*v2(0) - v2(2)*v1(0),
    v1(0)*v2(1) - v2(0)*v1(1)
  );
  
  Rcout << "normal: " <<  norm.X << ", " << norm.Y << ", " << norm.Z << std::endl;
  
  core::vector3df nomnom = norm.normalize();
  
  Rcout << "nomnomal: " <<  nomnom.X << ", " << nomnom.Y << ", " << nomnom.Z << std::endl;
  
  return norm;  
}

// https://stackoverflow.com/questions/45052226/
core::vector3df rotation_calc(DataFrame corner_points) {
  
  NumericVector x = corner_points["x"];
  NumericVector y = corner_points["y"];
  NumericVector z = corner_points["z"];
  
  // Z-axis
  core::vector3df zaxis(
      0, 0, 1
  );
  // resulting image's normal
  core::vector3df normal = normal_calc(corner_points);
  
  // calculate the rotation from the original image's normal (i.e. the Z-axis) 
  // to the resulting image's normal => quaternion P.
  core::quaternion p;
  p.rotationFromTo(zaxis, normal);
  
  // take the midpoint of AB from the diagram in method 1, and rotate it with 
  // the quaternion P => vector U.
  core::vector3df MAB(
      0, 0.5, 0
  );
  
  core::quaternion m(
      MAB.X, MAB.Y, MAB.Z, 0
  );
  
  core::quaternion rot = p * m * p.makeInverse();
  
  core::vector3df u(
    rot.X, rot.Y, rot.Z
  );
  
  // calculate the rotation from U to the midpoint of DE => quaternion Q
  core::vector3df MDE(
      (x(0) + x(1)) / 2,
      (y(0) + y(1)) / 2,
      (z(0) + z(1)) / 2
  );
  
  core::quaternion q;
  q.rotationFromTo(u, MDE);
  
  // multiply in the order Q * P, and convert to Euler angles
  core::quaternion f = q * p;
  
  core::vector3df euler;
  f.toEuler(euler);
  
  // to degrees
  core::vector3df degrees(
    euler.X * (180.0/3.14),
    euler.Y * (180.0/3.14),
    euler.Z * (180.0/3.14)
  );
  
  Rcout << "degrees: " <<  degrees.X << ", " << degrees.Y << ", " << degrees.Z << std::endl;
  
  return(degrees);
}
