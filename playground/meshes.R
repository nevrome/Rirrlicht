library(rgl)
library(Morpho)
library(magrittr)

rgl::cuboctahedron3d() -> hu

hu %>% rgl::plot3d()

rawConnection(raw(0), "r+") -> zz
m2p(x = hu, filename = zz)
rawConnectionValue(zz) %>%
  rawToChar() -> res1
close.connection(zz)


# my own mesh
vertices <- c( 
  -100.0, -100.0, 0, 100.0,
  50.0, -50.0, 0, 50.0,
  100.0,  100.0, 0, 100.0,
  -50.0,  50.0, 0, 50.0
)
indices <- c( 1, 2, 3, 4 )

qmesh3d(vertices, indices) -> huup # %>% wire3d() 


rawConnection(raw(0), "r+") -> zz
m2p(x = huup, filename = zz)
rawConnectionValue(zz) %>%
  rawToChar() -> res2
close.connection(zz)

#m2p(x = huup, filename = "~/test/hununu")

plot_irr(mesh_string_list = c(res1, res2))



rawConnection(raw(0), "r+") -> zz
mesh2obj(x = hu, filename = zz)
rawConnectionValue(zz) %>%
  rawToChar() -> res2
close.connection(zz)
