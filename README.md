[![Build Status](https://travis-ci.com/danoan/graph-flow.svg?branch=master)](https://travis-ci.com/danoan/graph-flow)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6059626d43064254affc2b908bcd86e1)](https://app.codacy.com/manual/danoan/graph-flow?utm_source=github.com&utm_medium=referral&utm_content=danoan/graph-flow&utm_campaign=Badge_Grade_Dashboard)
[![codecov](https://codecov.io/gh/danoan/graph-flow/branch/master/graph/badge.svg?token=15BDAZDRDS)](https://codecov.io/gh/danoan/graph-flow)


## graph-flow
 Implements a flow driven by Elastica energy minimization via graph-cuts.

 Its main applications are
 - **gf-shape-evolution**: Evolves a digital shape towards the shape of minimum Elastica energy. 
  - **gf-contour-correction**. Contour correction via Elastica regularization.
 - **interactive-seg**. Interactive segmentation with Elastica regularization.
 
 
## Dependencies 

[libboost1.70.0-dev](https://www.boost.org/users/history/version_1_70_0.html)

[opencv-3.4](https://opencv.org/releases.html)

[DGtal1.1](https://dgtal.org/download/)

[lemon1.3.1](https://lemon.cs.elte.hu/trac/lemon/wiki/Downloads)

qt5-default

zlib1g-dev

libgtk2.0-dev

## Build and Install

In order to build graph-flow, you are going to need cmake.

```
cd [GRAPHFLOW_ROOT_FOLDER]
mkdir build
cd build
cmake ..
make install
```

If 
all dependencies are installed in their standard
locations, that should be enough. Otherwise, if errors occur, 
it is likely that a manual configuration should be
done. In this scenario, **ccmake** (cmake-curses-gui package) is quite handy.

## How to use

This package contains six applications. For a detailed description,
type: [application_binary] -?

We give output examples of the main applications: gf-shape-evolution and interactive-seg

### gf-shape-evolution

Evolve a digital shape towards the shape of minimum Elastica energy

```
./gf-shape-evolution -Striangle -r15 -h0.1
./gf-shape-evolution -Sflower -r15 -h0.1
```

<img alt="Triangle flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/triangle.gif" width="1000" />
<img alt="Flower flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/flower.gif" width="1000" />


### interactive-seg

Load a image, select foreground/background seeds and then execute the gf-contour-correction algorithm.

```
./interactive-seg.sh -I input/images/coala.jpg output/coala
```
<img alt="Coala seeds" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seeds.png" height="300" /> <img alt="Coala segmentation" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seg.png" height="300" />

Check the influence of each parameter in this [report](https://danoan.github.io/content/papers/graph-flow-parameters/report.html).



