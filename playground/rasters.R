library(magrittr)
library(tibble)

images <- c("data-raw/berries.png", "data-raw/berries.png")
#images <- c("data-raw/berries.png")

images_corners1 <- tribble(
  ~x, ~y, ~z,
  0,5,0,
  0,10,0,
  1,5,5,
  1,10,5
) %>% as.data.frame()

images_corners2 <- tribble(
  ~x, ~y, ~z,
  0,5,0,
  0,10,0,
  5,5,0,
  5,10,0
) %>% as.data.frame()

plot_irr(
  points = data.frame(
    x = rnorm(500)*10, 
    y = rnorm(500)*10, 
    z = rnorm(500)*10,
    size = rnorm(500)/20 
  ),
  raster_paths_cv = images,
  #raster_corners_list = list(images_corners1),
  raster_corners_list = list(images_corners1, images_corners2),
  video_driver = "d"
)
