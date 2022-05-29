#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../.. && pwd )

APP_CONTOUR_CORRECTION=${PROJECT_PATH}/cmake-build-release/app/gf-segmentation/gf-segmentation
APP_SUMMARY_FLOW=${PROJECT_PATH}/cmake-build-release/app/summary-flow/summary-flow

python3 ${SCRIPT_PATH}/instance-generator/generator.py ${APP_CONTOUR_CORRECTION} ${APP_SUMMARY_FLOW} ${SCRIPT_PATH} ${SCRIPT_PATH}/output