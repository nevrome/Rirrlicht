library(magrittr)
library(tibble)

images <- c("data-raw/berries.png")
#images <- c("data-raw/berries.png", "data-raw/berries.png")
#images <- c("data-raw/berries.png", "data-raw/berries.png", "data-raw/berries.png")

# images_corners1 <- tribble(
#   ~x, ~y, ~z,
#   0,0,0,
#   1,0,0,
#   1,0,1,
#   0,0,1
# ) %>% as.data.frame()

# images_corners2 <- tribble(
#   ~x, ~y, ~z,
#   0,0,0,
#   0,2,0,
#   0,2,2,
#   0,0,2
# ) %>% as.data.frame()

# images_corners3 <- tribble(
#   ~x, ~y, ~z,
#   0,0,0,
#   3,0,0,
#   3,3,0,
#   0,3,0
# ) %>% as.data.frame()

images_corners2 <- tribble(
  ~x, ~y, ~z,
  0,3,0,
  5,-3,0,
  5,-3,3,
  0,3,3
) %>% as.data.frame()

plot_irr(
  raster_paths_cv = images,
  raster_corners_list = list(images_corners2),
  #raster_corners_list = list(images_corners1, images_corners3),
  #raster_corners_list = list(images_corners1, images_corners2, images_corners3),
  video_driver = "d"
)
