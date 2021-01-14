#!/bin/sh

echo "****Install Boost 1.70.0****"
$SCRIPT_BEGIN

    cd "${TEMP_DIR}"

    wget "https://dl.bintray.com/boostorg/release/1.70.0/source/boost_1_70_0.tar.gz"
    tar -xzvf "boost_1_70_0.tar.gz"
    rm "boost_1_70_0.tar.gz"

    mkdir -p "${DEPS_DIR}/include/boost"
    cp -R boost_1_70_0/boost "${DEPS_DIR}/include/boost"

    cd boost_1_70_0
    ./bootstrap.sh
    ./b2 --with-filesystem --with-system
    cp stage/lib/* "${DEPS_DIR}/lib/"

    cd "${TEMP_DIR}"
    rm -rf boost_1_70_0


$SCRIPT_END
