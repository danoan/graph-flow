#!/bin/sh

$SCRIPT_BEGIN

#############################
#     cmake
#############################
#Build directory
cd "$BUILD_DIR"

# Cmake
echo "Using C++ = $CXXCOMPILER"
cmake "$SRC_DIR" -DCMAKE_PREFIX_PATH="${DEPS_DIR}" -DCMAKE_INSTALL_PREFIX="${SRC_DIR}/install" \
-DBOOST_LIBS_DIR="${DEPS_DIR}/lib" -DBOOST_INCLUDE_DIRS="${DEPS_DIR}/include/boost" \
-DUSE_REMOTE_REPOSITORIES="ON" -DCMAKE_BUILD_TYPE=release -DBUILD_TESTS="ON"

make -j4
make install

# Building in debug because it is needed for test-coverage (gcov)
cmake "$SRC_DIR" -DCMAKE_PREFIX_PATH="${DEPS_DIR}" -DCMAKE_INSTALL_PREFIX="${SRC_DIR}/install" \
-DBOOST_LIBS_DIR="${DEPS_DIR}/lib" -DBOOST_INCLUDE_DIRS="${DEPS_DIR}/include/boost" \
-DUSE_REMOTE_REPOSITORIES="ON" -DCMAKE_BUILD_TYPE=debug -DBUILD_TESTS="ON"

make -j4

$SCRIPT_END