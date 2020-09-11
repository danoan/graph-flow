#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../.. && pwd )

APP_GRAPH_SEG="$1"
APP_SUMMARY_FLOW="$2"

if [ -z $APP_GRAPH_SEG ]; then
    APP_GRAPH_SEG=${PROJECT_PATH}/cmake-build-release/app/graph-seg/graph-seg-app
fi

if [ -z $APP_SUMMARY_FLOW ]; then
    APP_SUMMARY_FLOW=${PROJECT_PATH}/ext-projects/cmake-build-release/bin/summary-flow
fi


python3 ${SCRIPT_PATH}/instance-generator/generator.py ${SCRIPT_PATH} ${APP_GRAPH_SEG} ${APP_SUMMARY_FLOW} ${SCRIPT_PATH}/output