#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$(dirname "${BASH_SOURCE[0]}" )" > /dev/null 2>&1 && pwd)"
PROJECT_FOLDER="$(cd "${SCRIPT_FOLDER}" && cd ../../../.. && pwd)"

APP_GRAPH_SEG="$1"
APP_SUMMARY_FLOW="$2"

if [ -z $APP_GRAPH_SEG ]; then
    APP_GRAPH_SEG="${PROJECT_FOLDER}/cmake-build-release/app/graph-seg/graph-seg-app"
fi

if [ -z $APP_SUMMARY_FLOW ]; then
    APP_SUMMARY_FLOW=${PROJECT_PATH}/ext-projects/cmake-build-release/bin/summary-flow
fi


BRANCH_IMAGE="${SCRIPT_FOLDER}/branch-noisy.pgm"
OUTPUT_FOLDER="${SCRIPT_FOLDER}/output/noisy"

MAX_IT=1
it=1
while [ $it -le $MAX_IT ]; do
    $APP_GRAPH_SEG "${BRANCH_IMAGE}" "${OUTPUT_FOLDER}/curvature/${it}" -i-1 -N10 -g1 -k40 -A0.1 -B20 -O2 -a0 -s -n32 -h1 -r5
    it=$(($it+1))
done

it=1
while [ $it -le $MAX_IT ]; do
    $APP_GRAPH_SEG "${BRANCH_IMAGE}" "${OUTPUT_FOLDER}/fidelity/${it}" -i-1 -N10 -g1 -k1 -A1 -B1 -O2 -a0 -s -n32 -h1 -r5
    it=$(($it+1))
done