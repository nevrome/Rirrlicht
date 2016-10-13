# General roxygen tags
#' @useDynLib Rirrlicht
#' @importFrom Rcpp sourceCpp

#' @export
.onUnload <- function (libpath) {
  library.dynam.unload("Rirrlicht", libpath)
}