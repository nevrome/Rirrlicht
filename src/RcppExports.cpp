// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// normal_calc
NumericVector normal_calc(DataFrame corner_points);
RcppExport SEXP Rirrlicht_normal_calc(SEXP corner_pointsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< DataFrame >::type corner_points(corner_pointsSEXP);
    rcpp_result_gen = Rcpp::wrap(normal_calc(corner_points));
    return rcpp_result_gen;
END_RCPP
}
// plot_irr
bool plot_irr(Nullable<DataFrame> points_df, Nullable<CharacterVector> raster_paths_cv, Nullable<DataFrame> raster_corners_df, Nullable<CharacterVector> mesh_cv, bool doomhud, char video_driver);
RcppExport SEXP Rirrlicht_plot_irr(SEXP points_dfSEXP, SEXP raster_paths_cvSEXP, SEXP raster_corners_dfSEXP, SEXP mesh_cvSEXP, SEXP doomhudSEXP, SEXP video_driverSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Nullable<DataFrame> >::type points_df(points_dfSEXP);
    Rcpp::traits::input_parameter< Nullable<CharacterVector> >::type raster_paths_cv(raster_paths_cvSEXP);
    Rcpp::traits::input_parameter< Nullable<DataFrame> >::type raster_corners_df(raster_corners_dfSEXP);
    Rcpp::traits::input_parameter< Nullable<CharacterVector> >::type mesh_cv(mesh_cvSEXP);
    Rcpp::traits::input_parameter< bool >::type doomhud(doomhudSEXP);
    Rcpp::traits::input_parameter< char >::type video_driver(video_driverSEXP);
    rcpp_result_gen = Rcpp::wrap(plot_irr(points_df, raster_paths_cv, raster_corners_df, mesh_cv, doomhud, video_driver));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"Rirrlicht_normal_calc", (DL_FUNC) &Rirrlicht_normal_calc, 1},
    {"Rirrlicht_plot_irr", (DL_FUNC) &Rirrlicht_plot_irr, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_Rirrlicht(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
