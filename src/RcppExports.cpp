// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// plot_irr
bool plot_irr(NumericVector x, NumericVector y, NumericVector z, NumericVector size, char driverselect);
RcppExport SEXP Rirrlicht_plot_irr(SEXP xSEXP, SEXP ySEXP, SEXP zSEXP, SEXP sizeSEXP, SEXP driverselectSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type y(ySEXP);
    Rcpp::traits::input_parameter< NumericVector >::type z(zSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type size(sizeSEXP);
    Rcpp::traits::input_parameter< char >::type driverselect(driverselectSEXP);
    rcpp_result_gen = Rcpp::wrap(plot_irr(x, y, z, size, driverselect));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"Rirrlicht_plot_irr", (DL_FUNC) &Rirrlicht_plot_irr, 5},
    {NULL, NULL, 0}
};

RcppExport void R_init_Rirrlicht(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
