#!/bin/bash

SCRIPT_PATH=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)
PROJECT_ROOT=$(cd $SCRIPT_PATH && cd .. && pwd)
BUILD_FOLDER=${PROJECT_ROOT}/cmake-build-release

GCOV_FILES=${BUILD_FOLDER}/lab/test/coverage/CMakeFiles/test-coverage.dir
COVERAGE_OUTPUT_FOLDER=${PROJECT_ROOT}/lab/test/coverage/output

mkdir -p ${COVERAGE_OUTPUT_FOLDER}
cd ${COVERAGE_OUTPUT_FOLDER}

${BUILD_FOLDER}/lab/test/coverage/test-coverage

for gcnoFile in $(find ${GCOV_FILES} -name *.gcno)
do
  gcov $gcnoFile
done