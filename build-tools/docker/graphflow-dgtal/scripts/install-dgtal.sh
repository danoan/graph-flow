#!/bin/sh

echo "**** Install DGtal 1.1 ****"
$SCRIPT_BEGIN

    cd "${TEMP_DIR}"

    git clone "https://github.com/DGtal-team/DGtal" --single-branch --branch 1.1 --depth 1 "dgtal"

    cd "dgtal"
    mkdir "build"
    cd "build"

    cmake .. -DBUILD_EXAMPLES="OFF" \
    -DBUILD_TESTING="OFF" \
    -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}" \
    -DBoost_INCLUDE_DIR="${DEPS_DIR}/include/boost" \
    -DWITH_MAGICK="ON" \
    -DCMAKE_PREFIX_PATH="${CMAKE_PREFIX_PATH}"

    make install

    cd "${TEMP_DIR}"
    rm -rf "dgtal"

$SCRIPT_END
