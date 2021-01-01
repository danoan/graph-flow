#!/bin/sh

#SCRIPT_DIR defined in the docker image dipacus:env

# APP_GRAPH_FLOW="${SRC_DIR}/install/bin/gf-shape-evolution"
# APP_GRAPH_SEG="${SRC_DIR}/install/bin/gf-contour-correction"
# APP_SUMMARY_FLOW="${SRC_DIR}/install/bin/summary-flow"

# ./lab/test/flow/flow-always-improve/test-flow-always-improve.sh $APP_GRAPH_FLOW $APP_SUMMARY_FLOW
# ./lab/test/flow/flow-best-of-neighborhood/test-flow-best-of-neigh.sh $APP_GRAPH_FLOW $APP_SUMMARY_FLOW
# ./lab/test/seg/coala/test-seg.sh $APP_GRAPH_SEG $APP_SUMMARY_FLOW

./install/test/test-graph-flow-utils
./install/test/test-graph-flow-core
./install/test/test-graph-flow-io
./install/test/test-graph-flow-shape-evolution
./install/test/test-graph-flow-contour-correction