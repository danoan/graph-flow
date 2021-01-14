#!/bin/sh

rm -rf "${BUILD_DIR}"
rm -rf "${DEPS_DIR}"
rm -rf "${TEMP_DIR}"

echo "**** Preparing folders "${BUILD_DIR}", "${DEPS_DIR}" and "${TEMP_DIR}" ****"
mkdir "${BUILD_DIR}"
mkdir "${DEPS_DIR}"
mkdir "${TEMP_DIR}"
mkdir "${DEPS_DIR}/lib"
mkdir "${DEPS_DIR}/include"

