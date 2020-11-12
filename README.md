[![Build Status](https://travis-ci.com/danoan/graph-flow.svg?branch=master)](https://travis-ci.com/danoan/graph-flow)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6059626d43064254affc2b908bcd86e1)](https://app.codacy.com/manual/danoan/graph-flow?utm_source=github.com&utm_medium=referral&utm_content=danoan/graph-flow&utm_campaign=Badge_Grade_Dashboard)


## graph-flow
 Elastica-driven flow optmized via graph-cut based model. 
 Its main applications are the **graph-flow-app** 
 and ***interactive-seg** apps. The 
 latter integrates all the necessary steps to execute
 a segmentation regularized by the Elastica energy.
 
 
## Dependencies 

[libboost1.66.0-dev](https://www.boost.org/users/history/version_1_66_0.html)

[opencv-3.3.0](https://opencv.org/releases.html)

[DGtal0.9](https://dgtal.org/download/)

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

There are plenty of configuration parameters, but usually, if 
all dependencies are installed in their standard
locations, that should be enough. Otherwise, if errors occur, 
it is likely that a manual configuration should be
done. In this scenario, ccmake is quite handy.

## How to use

Build instructions can be found in INSTALL.txt

This source contains eight applications. For detailed description,
type: [application] -?

We give output examples of the main applications: graph-flow-app and interactive-seg

### graph-flow-app

Evolve the digital curvature flow for a given digital shape.

```
./graph-flow-app -Striangle -r15 -h0.1
./graph-flow-app -Sflower -r15 -h0.1
```

<img alt="Triangle flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/triangle.gif" width="1000" />
<img alt="Flower flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/flower.gif" width="1000" />


### interactive-seg

Load a image, select foreground/background seeds and then execute the graph-seg algorithm.

```
./interactive-seg.sh -I input/images/coala.jpg output/coala
```
<img alt="Coala seeds" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seeds.png" height="200" /> <img alt="Coala segmentation" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seg.png" height="200" />



