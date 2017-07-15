library(library)
library(jpeg)
library(tibble)
library(rgl)

download.file(
  url = 'https://upload.wikimedia.org/wikipedia/en/6/6d/Chewbacca-2-.jpg',
  destfile = "chewbacca.jpg",
  mode = 'wb'
)

chewie <- readJPEG("chewbacca.jpg", native = TRUE)

chewie_corners <- tribble(
  ~x, ~y, ~z,
  -2,-1,-3,
  1,-1,-3,
  1,1,2,
  -2,1,2
)

coolpicture <- function(image, position) {
  rgl::show2d( { 
      graphics::par(mar = rep(0, 4))
      graphics::plot( 0:1, 0:1, type = "n", ann = FALSE,
      axes = FALSE, xaxs = "i", yaxs = "i" )
      graphics::rasterImage(image, 0, 0, 1, 1)
    },
    x = position[, 1], y = position[, 2], z = position[, 3]
  )
}

rgl::plot3d(
  chewie_corners$x, 
  chewie_corners$y, 
  chewie_corners$z, col = "red", 
  size = 10,
  axes = FALSE,
  xlab = "", ylab = "", zlab = ""
)
coolpicture(chewie, chewie_corners)
