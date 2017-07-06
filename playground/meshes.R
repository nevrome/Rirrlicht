library(rgl)
library(magrittr)

rgl::cuboctahedron3d() %>%
  mesh2ply_string() %>%
  c(.) %>%
  plot_irr(mesh_cv = .)

hu %>% rgl::plot3d()

# my own mesh
vertices <- c( 
  -100.0, -100.0, 0, 100.0,
  50.0, -50.0, 0, 50.0,
  100.0,  100.0, 0, 100.0,
  -50.0,  50.0, 0, 50.0
)
indices <- c( 1, 2, 3, 4 )

qmesh3d(vertices, indices) -> huup # %>% wire3d() 

#### jpeg to string?

library(raster)

fnu <- raster("data-raw/berries.png")
