[![Build Status](https://travis-ci.com/danoan/graph-flow.svg?branch=master)](https://travis-ci.com/danoan/graph-flow)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/0d5ca9a759264e3eb2c5b3e907e76bf7)](https://www.codacy.com/gh/danoan/graph-flow/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=danoan/graph-flow&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/danoan/graph-flow/branch/master/graph/badge.svg?token=15BDAZDRDS)](https://codecov.io/gh/danoan/graph-flow)

# graph-flow
 Shape evolution and image segmentation by elastica regularization and graph cuts.

## Built-in executables

-  **gf-shape-evolution**: Evolves a digital shape towards the shape of minimum Elastica energy.
-  **interactive-seg**. Interactive segmentation with Elastica regularization.

## Running in a Docker container

Create a container from the image danoan/graphflow-vnc

```bash
docker run --rm -it danoan/graphflow:0.2.8.1vnc
```

To execute the applications, type

```bash
./graph-flow/install/bin/gf-shape-evolution <output_folder>
./graph-flow/interactive-seg.sh <output_folder>
```

It is recommended to create a vnc server in the container and access it via
a vnc client to make use of the graphical interface of the applications.

### Setting up the VNC server

Start the vnc server in the container

```bash
./graph-flow/scripts/start-vnc.sh
```

Next, check the container IP address with docker inspect

```bash
docker inspect <container_id>
```

With a VNC client, connect it to the container vnc server: <container_IP>:1

You should be able to access the container via a graphical interface now. Use
the flag `-d` to display the shape evolution.

```bash
./graph-flow/install/bin/gf-shape-evolution -d <output_folder>
```

## Manual build and installation

Before proceeding with the build and installation, make sure the dependencies below
are installed
### Dependencies

-  [libboost1.70.0-dev](https://www.boost.org/users/history/version_1_70_0.html)
-  [opencv-3.4](https://opencv.org/releases.html)
-  [DGtal1.1](https://dgtal.org/download/)
-  [lemon1.3.1](https://lemon.cs.elte.hu/trac/lemon/wiki/Downloads)
-  [cmake>=3.10](https://cmake.org/)
-  qt5-default
-  zlib1g-dev
-  libgtk2.0-dev
-  graphviz
-  g++
-  gfortran
-  libgraphicsmagick++1-dev
-  wget

Next, open a console and type the commands below

```bash
cd [GRAPHFLOW_ROOT_FOLDER]
mkdir build
cd build
cmake ..
make install
```

If all dependencies are installed in their standard
locations, that should be enough. Otherwise, if errors occur,
it is likely that a manual configuration should be
done. In this scenario, **ccmake** (cmake-curses-gui package) is quite handy.

## How to use

For a detailed description, type: <application_executable> -?

We give output examples of the main applications: gf-shape-evolution and interactive-seg

### gf-shape-evolution

Evolve a digital shape towards the shape of minimum elastica energy

```
./gf-shape-evolution -Striangle -r15 -h0.1
./gf-shape-evolution -Sflower -r15 -h0.1
```

<img alt="Triangle flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/triangle.gif" width="1000" />
<img alt="Flower flow" src="https://github.com/danoan/graph-flow/blob/master/doc/images/flower.gif" width="1000" />


### interactive-seg

Load a image, select foreground/background seeds and then execute the gf-segmentation algorithm.

```
./interactive-seg.sh -I input/images/coala.jpg output/coala
```
<img alt="Coala seeds" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seeds.png" height="300" /> <img alt="Coala segmentation" src="https://github.com/danoan/graph-flow/blob/master/doc/images/coala-seg.png" height="300" />

Check the influence of each parameter in this [report](https://danoan.github.io/content/papers/graph-flow/reports/parameter-tuning).
