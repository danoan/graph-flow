#!/bin/bash
SCRIPT_FOLDER="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

PROJECT_FOLDER="$(cd "$SCRIPT_FOLDER" && cd .. && pwd)"
GRAPH_SEG_BIN="${PROJECT_FOLDER}/cmake-build-release/app/graph-seg"

BTOOLS_BIN="${PROJECT_FOLDER}/ext-projects/cmake-build-release/bin"
INPUT_IMAGE="${PROJECT_FOLDER}/input/images/coala.jpg"

usage(){ echo "Usage: $0 "
echo "[-r Ball radius (default: 5)]"
echo "[-g Data regional term (default: 1.0) ]"
echo "[-b Data boundary term (default: 2.0) ]"
echo "[-k Squared curvature weight (default:2.5) ]"
echo "[-a Length weight (default:0.01) ]"
echo "[-i Max iterations (default:30) ]"
echo "[-w Print energy value ]"
echo "[-I INPUT_IMAGE_PATH (default:$INPUT_IMAGE) ]"
echo " OUTPUT_FOLDER" 1>&2; exit 1;}

r="7"
g="1.0"
b="2.0"
k="2.5"
a="0.01"
i="30"
w=""
while getopts ":r:g:b:k:a:i:I:w" o; do
    case "${o}" in
        r)
            r=$OPTARG
            ;;
        g)
            g=$OPTARG
            ;;
	    b)
	        b=$OPTARG
	        ;;
	    k)
	        k=$OPTARG
	        ;;
	    a)
	        a=$OPTARG
	        ;;
	    i)
	        i=$OPTARG
	        ;;
	    w)
	        w="-w"
	        ;;
	    I)
	        INPUT_IMAGE=$OPTARG
	        ;;
        :)
            echo "Invalid option: $OPTARG requires an argument" 1>&2
            exit 1;
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND -1))

OUTPUT_FOLDER="$1"
mkdir -p "$OUTPUT_FOLDER"

if [ -z "$OUTPUT_FOLDER" ]
then
    usage
    exit
fi

SEED_SELECTOR_APP="${BTOOLS_BIN}/seed-selector"
GRAB_CUT_APP="${BTOOLS_BIN}/grab-cut"
GRAPH_SEG_APP="${GRAPH_SEG_BIN}/graph-seg-app"


IMAGE_NAME="$(basename $INPUT_IMAGE)"
IMAGE_NAME="${IMAGE_NAME%%.*}"

SP_OUT="${OUTPUT_FOLDER}/${IMAGE_NAME}"
mkdir -p "$SP_OUT"


echo "Output files in: $SP_OUT"
echo ""

SEED_SELECTOR_OUT=""

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
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    "${GRAPH_SEG_APP}" "${SP_OUT}/gc-object.xml" -r"$r" -g"$g" -b"$b" -k"$k" -a"$a" -i"$i" -v -s ${w} "${SP_OUT}/graph-seg"
fi



while :
do
    "${SEED_SELECTOR_APP}" "${INPUT_IMAGE}" "$OUTPUT_FOLDER" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" \
    -f "${SP_OUT}/mask-fg-0.pgm" \
    -b "${SP_OUT}/mask-bg-0.pgm" -o

    if [ $? -eq 0 ]
    then
        exit
    fi

    "${GRAB_CUT_APP}" "${INPUT_IMAGE}" "${SP_OUT}/mask-fg-0.pgm" "${SP_OUT}/mask-bg-0.pgm" "${SP_OUT}/gc-object.xml" \
    -u "${SP_OUT}/mask-pbfg-0.pgm" -s

    "${GRAPH_SEG_APP}" "${SP_OUT}/gc-object.xml" -r"$r" -g"$g" -b"$b" -k"$k" -a"$a" -i"$i" -v -s ${w} "${SP_OUT}/graph-seg"
done

