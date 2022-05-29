#! /usr/bin/env bash

SCRIPT_FOLDER="$(cd $(dirname "${BASH_SOURCE[0]}") && pwd)"
PROJECT_FOLDER="${SCRIPT_FOLDER%graph-flow/*}graph-flow"

IMAGES_PATH="${SCRIPT_FOLDER}"

GRAPH_FLOW_ENV_IMAGE_PATH="${IMAGES_PATH}/graphflow-env/Dockerfile"
GRAPH_FLOW_DEPS_IMAGE_PATH="${IMAGES_PATH}/graphflow-deps/Dockerfile"
GRAPH_FLOW_DGTAL_IMAGE_PATH="${IMAGES_PATH}/graphflow-dgtal/Dockerfile"
GRAPH_FLOW_FULL_NO_VNC_IMAGE_PATH="${PROJECT_FOLDER}/Dockerfile"
GRAPH_FLOW_FULL_WITH_VNC_IMAGE_PATH="${IMAGES_PATH}/graphflow-with-vnc/Dockerfile"

function build_docker_image()
{
  local DOCKER_IMAGE_PATH="${1}"
  local DOCKER_IMAGE_NAME="${2}"
  local DEFAULT_WORK_DIR="$(dirname "${DOCKER_IMAGE_PATH}")"
  local BASE_WORK_DIR="${3:-"${DEFAULT_WORK_DIR}"}"

  docker build \
  -f"${DOCKER_IMAGE_PATH}" \
  -t "${DOCKER_IMAGE_NAME}" \
  "${BASE_WORK_DIR}"
}

build_docker_image "${GRAPH_FLOW_ENV_IMAGE_PATH}" "danoan/graphflow:env"
build_docker_image "${GRAPH_FLOW_DEPS_IMAGE_PATH}" "danoan/graphflow:deps"
build_docker_image "${GRAPH_FLOW_DGTAL_IMAGE_PATH}" "danoan/graphflow:dgtal1.1"
build_docker_image "${GRAPH_FLOW_FULL_NO_VNC_IMAGE_PATH}" "danoan/graphflow:v0.2.8.1" "${PROJECT_FOLDER}"
build_docker_image "${GRAPH_FLOW_FULL_WITH_VNC_IMAGE_PATH}" "danoan/graphflow:v0.2.8.1vnc"
