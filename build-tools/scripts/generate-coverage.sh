#!/bin/bash

SCRIPT_PATH="$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)"
PROJECT_ROOT="${SCRIPT_PATH%graph-flow/*}graph-flow"
BUILD_FOLDER="${PROJECT_ROOT}/cmake-build-release"

GCOV_FILES="${BUILD_FOLDER}/lab/test/coverage/CMakeFiles/test-coverage.dir"
COVERAGE_OUTPUT_FOLDER="${PROJECT_ROOT}/lab/test/coverage/output"
CODECOV_OUTPUT_FOLDER="${PROJECT_ROOT}/codecov"

mkdir -p ${COVERAGE_OUTPUT_FOLDER}

GCOV_BUILD="${PROJECT_ROOT}/gcov-build"
mkdir -p "${GCOV_BUILD}"

pushd "${GCOV_BUILD}" > /dev/null
gcov "${PROJECT_ROOT}/lab/test/coverage/test-coverage.cpp" --object-directory "${GCOV_FILES}"

lcov --capture --directory ${GCOV_FILES} --output-file ${COVERAGE_OUTPUT_FOLDER}/test_coverage.info
# genhtml "${COVERAGE_OUTPUT_FOLDER}/test_coverage.info" --output-directory "${COVERAGE_OUTPUT_FOLDER}/report"

bash <(curl -s https://codecov.io/bash)

popd > /dev/null