#!/bin/sh

#SCRIPT_DIR defined in the docker image dipacus:env

./lab/test/flow/flow-always-improve/test-flow-always-improve.sh
./lab/test/flow/flow-best-of-neighborhood/test-flow-best-of-neigh.sh
./lab/test/seg/coala/test-seg.sh