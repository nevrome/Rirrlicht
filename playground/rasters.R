library(magrittr)
library(tibble)

images <- c("data-raw/berries.png", "data-raw/berries.png")

images_corners1 <- tribble(
  ~x, ~y, ~z,
  0,0,0,
  0,1,0,
  1,1,0,
  1,0,0
) %>% as.data.frame()

images_corners2 <- tribble(
  ~x, ~y, ~z,
  0,0,0,
  0,1,0,
  1,1,0,
  1,0,0
) %>% as.data.frame()

plot_irr(
  raster_paths_cv = images,
  raster_corners_list = list(images_corners1, images_corners2)
)