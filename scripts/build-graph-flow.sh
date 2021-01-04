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
-DUSE_REMOTE_REPOSITORIES="ON" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS="ON"

make -j 1
make install

$SCRIPT_END