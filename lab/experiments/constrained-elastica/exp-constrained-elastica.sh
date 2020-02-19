#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../ && pwd )

APP_FLOW=${PROJECT_PATH}/cmake-build-release/app/graph-flow/graph-flow-app
APP_SUMMARY_FLOW=${PROJECT_PATH}/ext-projects/cmake-build-release/bin/summary-flow

LEN_PEN="0.1 0.01 0.001"

INPUT_FOLDER=${PROJECT_PATH}/input
BASE_OUTPUT_FOLDER=${SCRIPT_PATH}/output

convert_to_png()
{
    BASE_FOLDER=$1
    inkscape -z -e ${BASE_FOLDER}/summary.png -w 1024 -h 1024 ${BASE_FOLDER}/summary.svg
}


for lp in $LEN_PEN
do
    IN_FOLDER=${INPUT_FOLDER}/curve-3
    OUT_FOLDER=${BASE_OUTPUT_FOLDER}/curve-3/lp-${lp}
    mkdir -p ${OUT_FOLDER}

    $APP_FLOW -S${IN_FOLDER}/input.pgm -i100 -N0 -r7 -a${lp} -P${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}
    $APP_SUMMARY_FLOW ${OUT_FOLDER} -p${IN_FOLDER}/pixelMaskBig.pgm -d${IN_FOLDER}/dirMask.pgm ${OUT_FOLDER}/summary.svg

    convert_to_png $OUT_FOLDER
done

for lp in $LEN_PEN
do
    IN_FOLDER=${INPUT_FOLDER}/flower-1
    OUT_FOLDER=${BASE_OUTPUT_FOLDER}/flower-1/lp-${lp}
    mkdir -p ${OUT_FOLDER}

    $APP_FLOW -S${IN_FOLDER}/input.pgm -i100 -N0 -h1 -P${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}
    $APP_SUMMARY_FLOW ${OUT_FOLDER} -d${IN_FOLDER}/pixelMask.pgm ${OUT_FOLDER}/summary.svg

    convert_to_png $OUT_FOLDER
done