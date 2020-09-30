#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$(dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd)"
PROJECT_FOLDER="$(cd "${SCRIPT_FOLDER}" && cd ../../../.. && pwd)"

GRAPH_SEG_APP="${PROJECT_FOLDER}/cmake-build-release/app/graph-seg/graph-seg-app"
BRANCH_IMAGE="${SCRIPT_FOLDER}/input/line-cuts-noisy.pgm"
OUTPUT_FOLDER="${SCRIPT_FOLDER}/output/noisy"

MAX_IT=10
it=1
while [ $it -le $MAX_IT ]; do
    $GRAPH_SEG_APP "${BRANCH_IMAGE}" "${OUTPUT_FOLDER}/curvature/${it}" -i-1 -N10 -g1 -k10 -A0.1 -B10 -O2 -a0 -w -s -n32 -h1 -r5
    it=$(($it+1))
done

it=1
while [ $it -le $MAX_IT ]; do
    $GRAPH_SEG_APP "${BRANCH_IMAGE}" "${OUTPUT_FOLDER}/fidelity/${it}" -i-1 -N10 -g1 -k1 -A1 -B1 -O2 -a0 -w -s -n32 -h1 -r5
    it=$(($it+1))
done