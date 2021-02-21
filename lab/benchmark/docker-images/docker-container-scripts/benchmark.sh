VERSION="${1}"
SHAPE_EVOLUTION_APP="${SRC_DIR}/install/bin/graph-flow-app"

VERSION_SUFFIX="$(echo ${VERSION} | cut -d"." -f3)"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${SRC_DIR}/install/lib"

if [ ${VERSION_SUFFIX} -ge 4 ]
then
  SHAPE_EVOLUTION_APP="${SRC_DIR}/install/bin/gf-shape-evolution"
fi

OUTPUT_ROOT_FOLDER="${SRC_DIR}/benchmark/${VERSION}"
mkdir -p "${OUTPUT_ROOT_FOLDER}"

function formatTime(){
  TIME_STR="${1}"
  S=$( echo $TIME_STR | cut -d"s" -f1)
  MS=$( echo $TIME_STR | cut -d" " -f2 | cut -d"m" -f1)

  echo "${S}.${MS}"
}

function initResultsFile(){
  OUTPUT_FILE="${1}"
  PARAM="${2}"

  echo "${2},IT,TIME" > "${OUTPUT_FILE}"
}

function benchmark(){
  H="${1}"
  R="${2}"
  O="${3}"
  N="${4}"
  IT="${5}"
  SHAPE="${6}"
  VARY_PARAM="${7}"
  OUTPUT_FILE="${8}"


  TOTAL_TIME="0"
  i=1
  while [ $i -le 10 ]
  do
    DATA_TEMP_DIR="$(dirname ${OUTPUT_FILE})/data"
    mkdir -p ${DATA_TEMP_DIR}

    $SHAPE_EVOLUTION_APP -S${SHAPE} -h${H} -r${R} -O${O} -N${N} -i${IT} "${DATA_TEMP_DIR}"

    EXECUTION_TIME=$(tail -n1 "${DATA_TEMP_DIR}/energy.txt" | cut -d":" -f2)
    TIME_FMT="$(formatTime "${EXECUTION_TIME}")"

    TOTAL_TIME=$(python3 -c "print( ${TOTAL_TIME} + ${TIME_FMT})")

    rm -rf "${DATA_TEMP_DIR}"
    i=$(( $i+1))
  done

  MEAN_TIME=$(python3 -c "print( \"{:.3f}\".format(${TOTAL_TIME}/10.0 ))")
  echo "${!VARY_PARAM},${IT},${MEAN_TIME}" >> "${OUTPUT_FILE}"
  
}

# ************** Vary Grid Step *****************
echo "Vary Grid Step"
SQUARE_OUTPUT="${OUTPUT_ROOT_FOLDER}/square_H.csv"
FLOWER_OUTPUT="${OUTPUT_ROOT_FOLDER}/flower_H.csv"
initResultsFile "${SQUARE_OUTPUT}" "H"
initResultsFile "${FLOWER_OUTPUT}" "H"

  H="${1}"
  R="${2}"
  O="${3}"
  N="${4}"
  IT="${5}"

H_LIST="1.0 0.5 0.25 0.125"
for H in ${H_LIST}
do
  benchmark "${H}" "5" "2" "2" "10" "square" H "${SQUARE_OUTPUT}"
  benchmark "${H}" "5" "2" "2" "10" "flower" H "${FLOWER_OUTPUT}"
done
# ************************************************


# *********** Vary Estimation Radius **************
echo "Vary Estimation Radius"
SQUARE_OUTPUT="${OUTPUT_ROOT_FOLDER}/square_R.csv"
FLOWER_OUTPUT="${OUTPUT_ROOT_FOLDER}/flower_R.csv"
initResultsFile "${SQUARE_OUTPUT}" "R"
initResultsFile "${FLOWER_OUTPUT}" "R"

R_LIST="5 10 20"
for R in ${R_LIST}
do
  benchmark "0.25" "${R}" "2" "2" "10" "square" R "${SQUARE_OUTPUT}"
  benchmark "0.25" "${R}" "2" "2" "10" "flower" R "${FLOWER_OUTPUT}"
done
# ************************************************



# *********** Vary Optimization Band **************
echo "Vary Optimization Band"
SQUARE_OUTPUT="${OUTPUT_ROOT_FOLDER}/square_O.csv"
FLOWER_OUTPUT="${OUTPUT_ROOT_FOLDER}/flower_O.csv"
initResultsFile "${SQUARE_OUTPUT}" "O"
initResultsFile "${FLOWER_OUTPUT}" "O"

O_LIST="2 4 8"
for O in ${O_LIST}
do
  benchmark "0.25" "5" "${O}" "2" "10" "square" O "${SQUARE_OUTPUT}"
  benchmark "0.25" "5" "${O}" "2" "10" "flower" O "${FLOWER_OUTPUT}"
done
# ************************************************



# ************* Vary Neighborhood ****************
echo "Vary Neighborhood"
SQUARE_OUTPUT="${OUTPUT_ROOT_FOLDER}/square_N.csv"
FLOWER_OUTPUT="${OUTPUT_ROOT_FOLDER}/flower_N.csv"
initResultsFile "${SQUARE_OUTPUT}" "N"
initResultsFile "${FLOWER_OUTPUT}" "N"

N_LIST="2 4 8"
for N in ${N_LIST}
do
  benchmark "0.25" "5" "2" "${N}" "10" "square" N "${SQUARE_OUTPUT}"
  benchmark "0.25" "5" "2" "${N}" "10" "flower" N "${FLOWER_OUTPUT}"
done
# ************************************************