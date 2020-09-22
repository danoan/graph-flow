#!/bin/sh

#SCRIPT_DIR defined in the docker image dipacus:env

APP_GRAPH_FLOW="${SRC_DIR}/install/bin/graph-flow-app"
APP_GRAPH_SEG="${SRC_DIR}/install/bin/graph-seg-app"
APP_SUMMARY_FLOW="${SRC_DIR}/ext-projects/cmake-build-release/bin/summary-flow"

./lab/test/flow/flow-always-improve/test-flow-always-improve.sh $APP_GRAPH_FLOW $APP_SUMMARY_FLOW
./lab/test/flow/flow-best-of-neighborhood/test-flow-best-of-neigh.sh $APP_GRAPH_FLOW $APP_SUMMARY_FLOW
./lab/test/seg/coala/test-seg.sh $APP_GRAPH_SEG $APP_SUMMARY_FLOW