#!/bin/bash

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
PROJECT_ROOT=$(cd $SCRIPT_PATH && cd .. && pwd)
BUILD_FOLDER=${BUILD_DIR}

GCOV_FILES=${BUILD_FOLDER}/lab/test/coverage/CMakeFiles/test-coverage.dir
COVERAGE_OUTPUT_FOLDER=${PROJECT_ROOT}/lab/test/coverage/output
CODECOV_OUTPUT_FOLDER=${PROJECT_ROOT}/codecov

${BUILD_FOLDER}/lab/test/coverage/test-coverage
mkdir -p ${COVERAGE_OUTPUT_FOLDER}

lcov --capture --directory ${GCOV_FILES} --output-file ${COVERAGE_OUTPUT_FOLDER}/test_coverage.info
# genhtml "${COVERAGE_OUTPUT_FOLDER}/test_coverage.info" --output-directory "${COVERAGE_OUTPUT_FOLDER}/report"

bash <(curl -s https://codecov.io/bash)