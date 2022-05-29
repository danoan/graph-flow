#!/bin/sh

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

echo "**** Install Lemon 1.3.1 ****"
cd "${SCRIPT_PATH}"

tar xf "lemon-1.3.1.tar.xz"
cd "lemon-1.3.1"
mkdir "build"
cd "build"
cmake -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}" ..
make install
rm -rf "lemon-1.3.1"
