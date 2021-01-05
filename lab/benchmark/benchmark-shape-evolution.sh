SCRIPT_PATH="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
PROJECT_PATH="$(cd ${SCRIPT_PATH} && cd ../.. && pwd)"

VERSION="0.2.6"
SHAPE_EVOLUTION_APP="${PROJECT_PATH}/cmake-build-release/app/gf-shape-evolution/gf-shape-evolution"
OUTPUT_ROOT_FOLDER="${PROJECT_PATH}/lab/benchmark/output"

OUTPUT_FOLDER="${OUTPUT_ROOT_FOLDER}/$VERSION"

echo "Running gf-shape-evolution for square and flower shapes"
$SHAPE_EVOLUTION_APP -Ssquare -h0.25 -i100 "${OUTPUT_FOLDER}/square"&
$SHAPE_EVOLUTION_APP -Sflower -h0.25 -i100 "${OUTPUT_FOLDER}/flower"

SQUARE_TIME=$(tail -n1 "${OUTPUT_FOLDER}/square/energy.txt" | cut -d":" -f2)
FLOWER_TIME=$(tail -n1 "${OUTPUT_FOLDER}/flower/energy.txt" | cut -d":" -f2)

echo "Benchmark results for gf-shape-evolution (version:${VERSION})" > "${OUTPUT_FOLDER}/benchmark.txt"
echo "(shape=Square,it=100,h=.25):${SQUARE_TIME}" >> "${OUTPUT_FOLDER}/benchmark.txt"
echo "(shape=Flower,it=100,h=.25):${FLOWER_TIME}" >> "${OUTPUT_FOLDER}/benchmark.txt"