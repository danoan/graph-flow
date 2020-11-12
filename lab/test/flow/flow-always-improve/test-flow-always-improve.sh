#!/usr/bin/env bash

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
PROJECT_PATH=$( cd $SCRIPT_PATH && cd ../../../../ && pwd )

APP_GRAPH_FLOW="$1"
APP_SUMMARY_FLOW="$2"

if [ -z $APP_GRAPH_FLOW ]; then
    APP_GRAPH_FLOW=${PROJECT_PATH}/cmake-build-release/app/graph-flow/graph-flow-app
fi

if [ -z $APP_SUMMARY_FLOW ]; then
    APP_SUMMARY_FLOW=${PROJECT_PATH}/cmake-build-release/app/summary-flow/summary-flow
fi


python3 ${SCRIPT_PATH}/instance-generator/generator.py ${APP_GRAPH_FLOW} ${APP_SUMMARY_FLOW} ${SCRIPT_PATH}/output