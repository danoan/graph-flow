#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../../ && pwd )

APP_FLOW=${PROJECT_PATH}/cmake-build-release/app/gf-shape-evolution/gf-shape-evolution
APP_SUMMARY_FLOW=${PROJECT_PATH}/cmake-build-release/app/summary-flow/summary-flow

python3 ${SCRIPT_PATH}/instance-generator/generator.py ${APP_FLOW} ${APP_SUMMARY_FLOW} ${SCRIPT_PATH}/output