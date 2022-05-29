VERSION="${1}"
CONTOUR_CORRECTION_APP="${SRC_DIR}/install/bin/graph-seg-app"

VERSION_SUFFIX="$(echo ${VERSION} | cut -d"." -f3)"
export LD_LIBRARY_PATH="${LD_LIBRARY_PATH}:${SRC_DIR}/install/lib"

if [ ${VERSION_SUFFIX} -ge 4 ]
then
  CONTOUR_CORRECTION_APP="${SRC_DIR}/install/bin/gf-segmentation"
fi

COALA_GC_OBJECT_PATH="${SRC_DIR}/input/pre-processed/coala.xml"
OUTPUT_ROOT_FOLDER="${SRC_DIR}/benchmark-contour-correction/${VERSION}"
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
  H="1"
  R="${1}"
  O="${2}"
  N="${3}"
  IT="${4}"
  VARY_PARAM="${5}"
  OUTPUT_FILE="${6}"


  TOTAL_TIME="0"
  i=1
  while [ $i -le 10 ]
  do
    DATA_TEMP_DIR="$(dirname ${OUTPUT_FILE})/data"
    mkdir -p ${DATA_TEMP_DIR}

    if [ ${VERSION_SUFFIX} -ge 4 ]
    then
      $CONTOUR_CORRECTION_APP "${COALA_GC_OBJECT_PATH}" -r${R} -R${R} -O${O} -N${N} -i${IT} "${DATA_TEMP_DIR}"
    else
      $CONTOUR_CORRECTION_APP "${COALA_GC_OBJECT_PATH}" -h${H} -r${R} -O${O} -N${N} -i${IT} "${DATA_TEMP_DIR}"
    fi

    EXECUTION_TIME=$(tail -n1 "${DATA_TEMP_DIR}/energy.txt" | cut -d":" -f2)
    TIME_FMT="$(formatTime "${EXECUTION_TIME}")"

    TOTAL_TIME=$(python3 -c "print( ${TOTAL_TIME} + ${TIME_FMT})")

    rm -rf "${DATA_TEMP_DIR}"
    i=$(( $i+1))
  done

  MEAN_TIME=$(python3 -c "print( \"{:.3f}\".format(${TOTAL_TIME}/10.0 ))")
  echo "${!VARY_PARAM},${IT},${MEAN_TIME}" >> "${OUTPUT_FILE}"

}


# *********** Vary Estimation Radius **************
echo "Vary Estimation Radius"
COALA_OUTPUT="${OUTPUT_ROOT_FOLDER}/coala_R.csv"
initResultsFile "${COALA_OUTPUT}" "R"

R_LIST="5 10 20"
for R in ${R_LIST}
do
  benchmark "${R}" "2" "2" "10" R "${COALA_OUTPUT}"
done
# ************************************************



# *********** Vary Optimization Band **************
echo "Vary Optimization Band"
COALA_OUTPUT="${OUTPUT_ROOT_FOLDER}/coala_O.csv"
initResultsFile "${COALA_OUTPUT}" "O"

O_LIST="2 4 8"
for O in ${O_LIST}
do
  benchmark "5" "${O}" "2" "10" O "${COALA_OUTPUT}"
done
# ************************************************



# ************* Vary Neighborhood ****************
echo "Vary Neighborhood"
COALA_OUTPUT="${OUTPUT_ROOT_FOLDER}/coala_N.csv"
initResultsFile "${COALA_OUTPUT}" "N"

N_LIST="2 4 8"
for N in ${N_LIST}
do
  benchmark "5" "2" "${N}" "10" N "${COALA_OUTPUT}"
done
# ************************************************