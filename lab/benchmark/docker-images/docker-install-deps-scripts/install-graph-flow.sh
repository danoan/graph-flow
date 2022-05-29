GRAPH_FLOW_REPO="https://github.com/danoan/graph-flow"
GRAPH_FLOW_VERSION="${1}"
VERSION_SUFFIX="$(echo ${GRAPH_FLOW_VERSION} | cut -d"." -f3)"

if [ -z ${VERSION_SUFFIX} ]
then
  VERSION_SUFFIX=0
fi

cd "${TEMP_DIR}"
mkdir -p "${TEMP_DIR}"

git clone "${GRAPH_FLOW_REPO}" --single-branch --branch "${GRAPH_FLOW_VERSION}" --depth 1

cd graph-flow
mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX="${SRC_DIR}/install" \
-DBOOST_INCLUDE_DIRS="${DEPS_DIR}/include/boost" \
-DBOOST_LIBS_DIR="${DEPS_DIR}/lib" \
-DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH" \
-DCMAKE_BUILD_TYPE="Release" ..

make install

if [ ${VERSION_SUFFIX} -le 5 ]
then
  cd "${TEMP_DIR}/graph-flow"
  cp ext/magLac/cmake-build-release/lib/*.* "${SRC_DIR}/install/lib"
fi

mkdir -p "${SRC_DIR}/input/pre-processed"
cp "${TEMP_DIR}/graph-flow/input/pre-processed/coala.xml" "${SRC_DIR}/input/pre-processed/coala.xml"


cd "${TEMP_DIR}"
rm -rf graph-flow
