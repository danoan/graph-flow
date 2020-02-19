#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../ && pwd )

APP_FLOW=${PROJECT_PATH}/cmake-build-release/app/graph-flow/graph-flow-app
APP_SUMMARY_FLOW=${PROJECT_PATH}/ext-projects/cmake-build-release/bin/summary-flow

ORIENTATION="curve-1 curve-2 curve-3"
FIXED="flower-1 flower-2"

INPUT_FOLDER=${PROJECT_PATH}/input
BASE_OUTPUT_FOLDER=${SCRIPT_PATH}/output

for f in $ORIENTATION
do
    IN_FOLDER=${INPUT_FOLDER}/${f}
    OUT_FOLDER=${BASE_OUTPUT_FOLDER}/${f}
    mkdir -p ${OUT_FOLDER}

    $APP_FLOW -S${IN_FOLDER}/input.pgm -i100 -N0 -r7 -P${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}
    $APP_SUMMARY_FLOW ${OUT_FOLDER} -d${IN_FOLDER}/dirMask.pgm ${OUT_FOLDER}/summary.svg
done

for f in $FIXED
do
    IN_FOLDER=${INPUT_FOLDER}/${f}
    OUT_FOLDER=${BASE_OUTPUT_FOLDER}/${f}
    mkdir -p ${OUT_FOLDER}

    $APP_FLOW -S${IN_FOLDER}/input.pgm -i100 -N0 -h1 -P${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}
    $APP_SUMMARY_FLOW ${OUT_FOLDER} -d${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}/summary.svg
done
