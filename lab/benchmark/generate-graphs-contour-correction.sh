SCRIPT_PATH="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
PROJECT_PATH="$(cd ${SCRIPT_PATH} && cd ../.. && pwd)"

#DOES NOT WORK IF THE PATH HAS SPACES!!!!

source "${SCRIPT_PATH}/config.sh"

function generate_graph(){
  GRAPH_TITLE="${1}"
  OUTPUT_FILEPATH="${2}"
  DATA_FILE_BASE_NAME="${3}"


  DATA_FOLDER="${SCRIPT_PATH}/output/benchmark-contour-correction"
  CSV_DATA_PATHS=""
  NVERSIONS=0
  for V in ${VERSIONS}
  do
    CSV_DATA_PATHS="${CSV_DATA_PATHS} v${V}  ${DATA_FOLDER}/${V}/${DATA_FILE_BASE_NAME}"
    NVERSIONS=$(( ${NVERSIONS}+1 ))
  done

  CSV_DATA_CURRENT_VERSION="v${CURRENT_VERSION}  ${DATA_FOLDER}/${CURRENT_VERSION}/${DATA_FILE_BASE_NAME}"
  NVERSIONS=$(( ${NVERSIONS}+1 ))

  python3 "${SCRIPT_PATH}/plot-bars.py" \
  "${GRAPH_TITLE}" \
  "${OUTPUT_FILEPATH}" \
  ${NVERSIONS} \
  ${CSV_DATA_PATHS} \
  ${CSV_DATA_CURRENT_VERSION}
}

OUTPUT_FOLDER="${SCRIPT_PATH}/output/benchmark-contour-correction/graphs"
mkdir -p "${OUTPUT_FOLDER}"


generate_graph "Estimation radius variation for coala" "${OUTPUT_FOLDER}/coala_R.png" "coala_R.csv"
generate_graph "Optimization band variation for coala" "${OUTPUT_FOLDER}/coala_O.png" "coala_O.csv"
generate_graph "Neighborhood size variation for coala" "${OUTPUT_FOLDER}/coala_N.png" "coala_N.csv"
