#!/usr/bin/env bash

SCRIPT_FOLDER=$( cd $(dirname ${BASH_SOURCE[0]}) >/dev/null 2>&1 && pwd)
PROJECT_FOLDER=$( cd $SCRIPT_FOLDER && cd ../../../.. && pwd )

DATA_FOLDER=${SCRIPT_FOLDER}/input
EXT_FOLDER=${SCRIPT_FOLDER}/ext
OUTPUT_FOLDER=${SCRIPT_FOLDER}/output

mkdir -p ${OUTPUT_FOLDER}/schoenemann
mkdir -p ${OUTPUT_FOLDER}/graph-seg

IMAGES_FOLDER=${DATA_FOLDER}/seg-bench/images
GS_SEEDS_FOLDER=${DATA_FOLDER}/seg-bench/graph-seg/seeds

GRAB_CUT_APP=${PROJECT_FOLDER}/cmake-build-release/app/grabcut/grabcut
GRAPH_SEG_APP=${PROJECT_FOLDER}/cmake-build-release/app/gf-segmentation/gf-segmentation

replace_line()
{
    FILE=$1
    LINE_NUMBER=$2
    NEW_TEXT="$3"

    T1=$(($LINE_NUMBER - 1))
    T2=$(($LINE_NUMBER + 1))

    head $FILE -n$T1 > .temp.part1
    tail $FILE -n+$T2 > .temp.part2

    echo $NEW_TEXT >> .temp.part1
    cat .temp.part1 .temp.part2 > $1

    rm .temp.part1 .temp.part2
}

find_line_number_first_ocurrence()
{
    TEXT_TO_FIND="$1"
    FILE=$2

    echo $(grep "${TEXT_TO_FIND}"  $FILE -n | head -n1 | cut -d: -f1)
}


init()
{
    tar -xvf ${DATA_FOLDER}/seg-bench.tar.bz2 -C ${DATA_FOLDER}
}


produce_data()
{
    for imgName in $(ls ${GS_SEEDS_FOLDER})
    do
        echo "Creating GS gc-object for ${imgName}"
        $GRAB_CUT_APP ${IMAGES_FOLDER}/${imgName}.jpg \
        ${GS_SEEDS_FOLDER}/${imgName}/mask-fg-0.pgm \
        ${GS_SEEDS_FOLDER}/${imgName}/mask-bg-0.pgm \
        ${GS_SEEDS_FOLDER}/${imgName}/gc-object.xml \
        -u ${GS_SEEDS_FOLDER}/${imgName}/mask-pbfg-0.pgm
    done

}

produce_output()
{
    i=1
    for imgName in $(ls ${GS_SEEDS_FOLDER})
    do
        echo "Graph Segmentation of image ${GS_SEEDS_FOLDER}/${imgName}"
        $GRAPH_SEG_APP -i-1 -r16 -R16 -G1.0 -g1.0 -K2.0 -k2.0 -a0 -O4 -N2 -n6 "${GS_SEEDS_FOLDER}/${imgName}/gc-object.xml"  \
        "${OUTPUT_FOLDER}/graph-seg/${imgName}"&

        if [ $i = "4" ]
        then
            wait
            i=0
        fi
        i=$[$i+1]
    done
}

# init
# produce_data
produce_output