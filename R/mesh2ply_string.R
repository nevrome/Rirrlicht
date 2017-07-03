#' mesh2ply string version
#' 
#' Mask for Morpho::mesh2ply
#' 
#' @param mesh truet
#' 
#' @return string that describes a mesh in ply format
#' 
#' @importFrom magrittr "%>%"
#' 
#' @export
mesh2ply_string <- function(mesh) { 
  rawConnection(raw(0), "r+") -> zz
  Morpho::mesh2ply(x = mesh, filename = zz)
  rawConnectionValue(zz) %>%
    rawToChar() -> res
  close.connection(zz)
  return(res)
}
