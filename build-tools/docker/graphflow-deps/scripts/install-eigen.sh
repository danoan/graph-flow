#!/bin/sh

$SCRIPT_BEGIN

echo "****Install Eigen 3.2.10****"
echo $TRAVIS_OS_NAME

    cd "${TEMP_DIR}"

    wget "https://gitlab.com/libeigen/eigen/-/archive/3.2.10/eigen-3.2.10.tar.bz2"
    bunzip2 "eigen-3.2.10.tar.bz2"
    tar xf "eigen-3.2.10.tar"

    cd "eigen-3.2.10"
    mkdir "build" ; cd "build"

    cmake .. -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}"
    make install

    cd "${TEMP_DIR}"
    rm "eigen-3.2.10.tar"
    rm -rf "eigen-3.2.10"

$SCRIPT_END
