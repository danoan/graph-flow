#!/bin/sh

echo "**** Install OpenCV 3.4****"
$SCRIPT_BEGIN
    cd "${TEMP_DIR}"

    git clone "https://github.com/opencv/opencv" --single-branch --branch 3.4 --depth 1 "opencv3.4"

    cd "opencv3.4"
    mkdir "build" ; cd "build"

    cmake .. -DCMAKE_INSTALL_PREFIX="${DEPS_DIR}" \
-DBUILD_TESTS="OFF" \
-DBUILD_EXAMPLES="OFF" \
-DBUILD_PERF_TESTS="OFF" \
-DBUILD_opencv_apps="OFF" \
-DBUILD_opencv_calib3d="ON" \
-DBUILD_opencv_dnn="OFF" \
-DBUILD_opencv_features2d="OFF" \
-DBUILD_opencv_java_bindings_gen="OFF" \
-DBUILD_opencv_python_tests="OFF" \
-DBUILD_opencv_shape="OFF" \
-DBUILD_opencv_stiching="OFF" \
-DBUILD_opencv_superres="OFF" \
-DBUILD_opencv_ts="OFF" \
-DBUILD_opencv_video="OFF" \
-DBUILD_opencv_videoio="OFF" \
-DBUILD_opencv_videostab="OFF" \
-DWITH_GTK="ON" \
-DWITH_GTK_2_X="ON" \
-DWITH_QT="ON"

    make install

    cd "${TEMP_DIR}"
    rm -rf "opencv3.4"

$SCRIPT_END
