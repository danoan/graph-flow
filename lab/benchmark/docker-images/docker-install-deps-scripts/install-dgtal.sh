DGTAL_REPO="https://github.com/DGtal-team/DGtal"
DGTAL_VERSION="${1}"

cd "${TEMP_DIR}"
mkdir -p "${TEMP_DIR}"

git clone "${DGTAL_REPO}" --single-branch --branch "${DGTAL_VERSION}" --depth 1 dgtal

cd dgtal
mkdir build
cd build

cmake .. -DBUILD_EXAMPLES="OFF" -DBUILD_TESTING="OFF" -DCMAKE_INSTALL_PREFIX="$DEPS_DIR" \
-DBoost_INCLUDE_DIR="$DEPS_DIR/include/boost" -DCMAKE_PREFIX_PATH="$CMAKE_PREFIX_PATH"

make install

cd "${TEMP_DIR}"
rm -rf dgtal
