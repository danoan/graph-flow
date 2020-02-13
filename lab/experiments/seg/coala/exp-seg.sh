#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../.. && pwd )

APP_FLOW=${PROJECT_PATH}/cmake-build-release/app/graph-seg/graph-seg-app
APP_SUMMARY_FLOW=${PROJECT_PATH}/ext-projects/cmake-build-release/bin/summary-flow

python3 ${SCRIPT_PATH}/instance-generator/generator.py ${PROJECT_PATH} cmake-build-release ${APP_SUMMARY_FLOW} ${SCRIPT_PATH}/output