SCRIPT_PATH="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
PROJECT_PATH="$(cd ${SCRIPT_PATH} && cd ../.. && pwd)"

source "config.sh"

DOCKER_IMAGES_FOLDER="${SCRIPT_PATH}/docker-images"
OUTPUT_FOLDER="${SCRIPT_PATH}/output"

mkdir -p "${OUTPUT_FOLDER}/benchmark"

#Build DGtal docker images
cd "${DOCKER_IMAGES_FOLDER}"
docker build . -f Dockerfile-dgtal-0.9.4 -t graphflow:dgtal-0.9.4
# docker build . -f Dockerfile-dgtal-1.1 -t graphflow:dgtal-1.1

#Build graph-flow docker images
for V in ${VERSIONS}
do
  docker build "${DOCKER_IMAGES_FOLDER}" -f Dockerfile-gf-v${V} -t graphflow:v${V}
done

#Run benchmarks in container
for V in ${VERSIONS}
do
  docker run --name container-gf-v${V} graphflow:v${V} bash /app/scripts/benchmark.sh ${V}
  docker cp container-gf-v${V}:/app/benchmark "${OUTPUT_FOLDER}"
  docker rm container-gf-v${V}
done

#Benchmark current version
export SRC_DIR="${PROJECT_PATH}"
BENCHMARK_SCRIPT="${SCRIPT_PATH}/docker-images/docker-container-scripts/benchmark.sh"

${BENCHMARK_SCRIPT} ${CURRENT_VERSION}
mv "${PROJECT_PATH}/benchmark/${CURRENT_VERSION}" "${SCRIPT_PATH}/output/benchmark"
rm -rf "${PROJECT_PATH}/benchmark"


