SCRIPT_PATH="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
PROJECT_PATH="$(cd ${SCRIPT_PATH} && cd ../.. && pwd)"

#DOES NOT WORK IF THE PATH HAS SPACES!!!!

source "config.sh"

function generate_graph(){
  GRAPH_TITLE="${1}"
  OUTPUT_FILEPATH="${2}"
  DATA_FILE_BASE_NAME="${3}"


  DATA_FOLDER="${SCRIPT_PATH}/output/benchmark"
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

OUTPUT_FOLDER="${SCRIPT_PATH}/output/benchmark/graphs"
mkdir -p "${OUTPUT_FOLDER}"

SHAPES="square flower"

for SHAPE in $SHAPES
do
  generate_graph "Grid step variation for ${SHAPE}" "${OUTPUT_FOLDER}/${SHAPE}_H.png" "${SHAPE}_H.csv"
  generate_graph "Estimation radius variation for ${SHAPE}" "${OUTPUT_FOLDER}/${SHAPE}_R.png" "${SHAPE}_R.csv"
  generate_graph "Optimization band variation for ${SHAPE}" "${OUTPUT_FOLDER}/${SHAPE}_O.png" "${SHAPE}_O.csv"
  generate_graph "Neighborhood size variation for ${SHAPE}" "${OUTPUT_FOLDER}/${SHAPE}_N.png" "${SHAPE}_N.csv"
done

