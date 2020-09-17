#!/usr/bin/env bash

SCRIPT_FOLDER="$( cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd )"
PROJECT_PATH="$( cd "${SCRIPT_FOLDER}" && cd ../.. && pwd)"

GRAPH_SEG_APP="${PROJECT_PATH}/cmake-build-release/app/graph-seg/graph-seg-app"
RANDOM_SEEDS_APP="${PROJECT_PATH}/cmake-build-release/app/random-seeds/random-seeds-app"
GRAB_CUT_APP="${PROJECT_PATH}/ext-projects/cmake-build-release/bin/grab-cut"
SEED_SELECTOR_APP="${PROJECT_PATH}/ext-projects/cmake-build-release/bin/seed-selector"

NCENTERS=100
RADIUS=15

INPUT_IMAGE="$1"
IMAGE_NAME="$(basename $INPUT_IMAGE)"
IMAGE_NAME="${IMAGE_NAME%%.*}"

OUTPUT_FOLDER="/home/dantu/GIT/PhD/graph-flow/output/graph-seg-random"
SP_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}"
GS_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}/graph-seg"




if [ ! -f "${SP_OUT}/mask-bg-0.pgm" ]
then
    "${SEED_SELECTOR_APP}" "${INPUT_IMAGE}" "${OUTPUT_FOLDER}" -o
    if [ $? -eq 0 ]
    then
        exit
    fi

    "${GRAB_CUT_APP}" "${INPUT_IMAGE}" "${SP_OUT}/mask-fg-0.pgm" \
    "${SP_OUT}/mask-bg-0.pgm" \
    "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -d

    ${GRAPH_SEG_APP} "${SP_OUT}/gc-object.xml" "${GS_OUT}" -r7 -a0.01 -h0.25 -k2.5 -g1 -i5 -v -w
fi



while :
do
    "${SEED_SELECTOR_APP}" "${INPUT_IMAGE}" "${OUTPUT_FOLDER}" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" \
    -f "${SP_OUT}/mask-fg-0.pgm" \
    -b "${SP_OUT}/mask-bg-0.pgm" \
    -s "${GS_OUT}/mask-seg.pgm" -o

    if [ $? -eq 0 ]
    then
        exit
    fi

    "${GRAB_CUT_APP}" "${INPUT_IMAGE}" "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s "${GS_OUT}/mask-seg.pgm"

    ${RANDOM_SEEDS_APP} "${SP_OUT}/gc-object.xml" "${NCENTERS}" "${RADIUS}" "${GS_OUT}/random-seeds.pgm" "${GS_OUT}/mask-seg.pgm"
    ${GRAPH_SEG_APP} "${SP_OUT}/gc-object.xml" "${GS_OUT}" -r7 -a0.01 -h0.25 -k2.5 -g1 -i20 -v -w -R "${GS_OUT}/random-seeds.pgm"
done


