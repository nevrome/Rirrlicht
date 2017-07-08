library(magrittr)
library(tibble)

images <- c("data-raw/berries.png")

images_corners <- tribble(
  ~x, ~y, ~z,
  0,0,0,
  0,0,1,
  1,0,1,
  1,0,0
) %>% as.data.frame()

plot_irr(
  raster_paths_cv = images,
  raster_corners_df = images_corners
)