library(rgl)
library(Morpho)
library(magrittr)

rgl::cuboctahedron3d() -> hu

hu %>% rgl::plot3d()

rawConnection(raw(0), "r+") -> zz
m2p(x = hu, filename = zz)
rawConnectionValue(zz) %>%
  rawToChar() -> res
close.connection(zz)

res


