[![license](https://img.shields.io/badge/license-GPL%202-B50B82.svg)](http://www.r-project.org/Licenses/GPL-2)

Rirrlicht
---------

R package to provide an API for the [Irrlicht engine](http://irrlicht.sourceforge.net/). Two functions as a proof of concept. I'm not part of the Irrlicht Engine team and I'm not actively working on this -- feel free to take it over.

Installation
------------

1. [Install Irrlicht](http://irrlicht.sourceforge.net/?page_id=10).

2. Install this package.

```{r}
# install.packages("devtools")
devtools::install_github("nevrome/Rirrlicht")
``` 

3. Test it.

```{r}
library(Rirrlicht)

irrmesh(
  "data-raw/farao.md2", 
  "data-raw/farao.bmp", 
  "a"
)

irrscatter(
  x = rnorm(500)*200, 
  y = rnorm(500)*200, 
  z = rnorm(500)*200, 
  size = rnorm(500)*10, 
  driverselect = "a"
)
``` 