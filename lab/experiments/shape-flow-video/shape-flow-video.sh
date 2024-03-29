#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH="$( cd "$SCRIPT_PATH" && cd ../../.. && pwd)"

GRAPH_FLOW_APP="${PROJECT_PATH}/cmake-build-release/app/gf-shape-evolution/gf-shape-evolution"
DATA_FOLDER="${SCRIPT_PATH}/data"

CACHE_TEMP_PATH="${SCRIPT_PATH}/cache"
mkdir -p $CACHE_TEMP_PATH

SHAPES="square 150 triangle 250 flower 300 bean 400"

flow()
{
    s=$1; shift;
    it=$1; shift;
    while [ -n "$s" ]
    do
       echo "Executing flow for shape ${s^}"
       ${GRAPH_FLOW_APP} -S"$s" -i$it -r15 -N3 -h0.1 -a0.01 -b1 -n10 -s ${DATA_FOLDER}/${s}

       s="$1"; shift;
       it="$1"; shift;
    done
}

animated_gif()
{
    s=$1; shift;
    it=$1; shift;
    while [ -n "$s" ]
    do

       OUTPUT_FOLDER=${SCRIPT_PATH}/output
       ${SCRIPT_PATH}/make-plot-frames.sh ${s} ${OUTPUT_FOLDER} ${CACHE_TEMP_PATH}

       ${SCRIPT_PATH}/join-gifs.sh ${DATA_FOLDER}/${s} ${s} ${OUTPUT_FOLDER}/${s}/flow-plot.gif ${CACHE_TEMP_PATH}

       s="$1"; shift;
       it="$1"; shift;
    done

}

mkdir ${PROJECT_PATH}/temp
export MAGICK_TMPDIR=${PROJECT_PATH}/temp

flow $SHAPES
animated_gif $SHAPES
rm -rf MAGICK_TMPDIR
