#!/bin/sh

echo "**** Install Lemon 1.3.1 ****"
cd "${TEMP_DIR}/lemon-1.3.1"
mkdir "build"
cd "build"
cmake -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}" ..
make install
cd "${TEMP_DIR}"
rm -rf "lemon-1.3.1"
