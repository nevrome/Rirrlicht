library(magrittr)
library(tibble)

images <- c("data-raw/berries.png", "data-raw/berries.png")

images_corners1 <- tribble(
  ~x, ~y, ~z,
  0,5,0,
  -2,5,5,
  0,10,0,
  -2,10,5
) %>% as.data.frame()

images_corners2 <- tribble(
  ~x, ~y, ~z,
  0,5,0,
  5,5,2,
  0,10,0,
  5,10,2
) %>% as.data.frame()

plot_irr(
  raster_paths_cv = images,
  raster_corners_list = list(images_corners1, images_corners2)
)