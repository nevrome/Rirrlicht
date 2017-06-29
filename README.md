[![Travis-CI Build Status](https://travis-ci.org/nevrome/Rirrlicht.svg?branch=master)](https://travis-ci.org/nevrome/Rirrlicht) [![Coverage Status](https://img.shields.io/codecov/c/github/nevrome/Rirrlicht/master.svg)](https://codecov.io/github/nevrome/Rirrlicht?branch=master)
[![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/Rirrlicht)](http://cran.r-project.org/package=Rirrlicht)
[![license](https://img.shields.io/badge/license-GPL%202-B50B82.svg)](https://www.r-project.org/Licenses/GPL-2)

Rirrlicht
---------

R package to provide a plot API for the [Irrlicht engine](http://irrlicht.sourceforge.net/).

I'm not part of the Irrlicht Engine team -- this is just an API.

Installation
------------

1 -- [Install Irrlicht](http://irrlicht.sourceforge.net/?page_id=10).

2 -- Install this package.

```{r}
# install.packages("devtools")
devtools::install_github("nevrome/Rirrlicht")
``` 

3 -- Test it.

```{r}
library(Rirrlicht)

plot_irr(
  points = data.frame(
    x = rnorm(500)*200, 
    y = rnorm(500)*200, 
    z = rnorm(500)*200,
    size = rnorm(500)*10 
  )
)
``` 