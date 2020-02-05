cmake_minimum_required(VERSION 3.14)
project(graph-flow)

set(CMAKE_CXX_STANDARD 20)
set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext-projects/source)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-release)
else()
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext-projects/cmake-build-debug)
endif ()

set(DIPACUS_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "DIPaCUS include location path.")
set(DIPACUS_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "DIPaCUS libraries location path.")

set(GCURVE_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "GCurve include location path.")
set(GCURVE_LIBS_DIR ${EXTPROJECTS_BUILD_DIR}/lib CACHE PATH "GCurve libraries location path.")

set(GEOC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "GEOC include location path.")
set(MAGLAC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "MagLac include location path.")

set(LEMON_INCLUDE_DIRS ${CMAKE_PREFIX_PATH}/include CACHE PATH "Lemon include location path.")
set(LEMON_LIBS_DIR ${CMAKE_PREFIX_PATH}/lib CACHE PATH "Lemon libraries location path.")

add_subdirectory(ext-projects)
add_subdirectory(modules/core)
add_subdirectory(modules/utils)
add_subdirectory(app/graph-flow)

