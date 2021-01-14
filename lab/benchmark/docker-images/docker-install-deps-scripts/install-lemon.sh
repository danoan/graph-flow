LEMON_SOURCE_PATH="http://lemon.cs.elte.hu/pub/sources/lemon-1.3.1.tar.gz"

mkdir -p "${TEMP_DIR}"
cd "${TEMP_DIR}"

wget "${LEMON_SOURCE_PATH}"
gunzip lemon-1.3.1.tar.gz
tar xf lemon-1.3.1.tar

cd "lemon-1.3.1"

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}" ..
make install

cd ${TEMP_DIR}
rm -rf lemon-1.3.1
