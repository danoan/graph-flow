cmake_minimum_required(VERSION 3.10)
project(graph-flow)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXTPROJECTS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext)
set(CMAKE_Swift_NUM_THREADS 2)

add_definitions(-DMY_MAIN_DIR="${CMAKE_SOURCE_DIR}")

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

if (${CMAKE_BUILD_TYPE} STREQUAL release)
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext/cmake-build-release)
else()
    set(EXTPROJECTS_BUILD_DIR ${CMAKE_SOURCE_DIR}/ext/cmake-build-debug)
endif ()

message("Build directory: ${CMAKE_BINARY_DIR}")

set(MAGLAC_INCLUDE_DIRS ${EXTPROJECTS_BUILD_DIR}/include CACHE PATH "MagLac include location path.")

set(LEMON_INCLUDE_DIRS ${CMAKE_PREFIX_PATH}/include CACHE PATH "Lemon include location path.")
set(LEMON_LIBS_DIR ${CMAKE_PREFIX_PATH}/lib CACHE PATH "Lemon libraries location path.")

set(BOOST_INCLUDE_DIRS /usr/local/include/boost CACHE PATH "Boost include location path." )
set(BOOST_LIBS_DIR /usr/local/lib CACHE PATH "Boost libraries location path.")

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "graph-flow binaries and libraries install location." )
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib:${BOOST_LIBS_DIR}:${LEMON_LIBS_DIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CREATE_SHARED_LIBRARIES ON CACHE BOOL "Create shared libraries. If off, create static libraries.")
set(USE_REMOTE_REPOSITORIES ON CACHE BOOL "Pull external repositories from GitHub.")

set(BUILD_TESTS OFF CACHE BOOL "Build tests.")
set(BUILD_APPS ON CACHE BOOL "Build applications.")

if (${USE_REMOTE_REPOSITORIES})
    add_subdirectory(ext)
endif ()

link_directories(${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${CMAKE_BINARY_DIR}/modules/io/seed
        ${CMAKE_BINARY_DIR}/modules/shape-evolution
        ${CMAKE_BINARY_DIR}/modules/contour-correction
        ${LEMON_LIBS_DIR}
        ${BOOST_LIBS_DIR}
        ${DGTAL_LIBS_DIR})


add_subdirectory(modules/core)
add_subdirectory(modules/utils)
add_subdirectory(modules/io/seed)
add_subdirectory(modules/shape-evolution)
add_subdirectory(modules/contour-correction)

if(${BUILD_APPS})
    add_subdirectory(app/gf-shape-evolution)
    add_subdirectory(app/gf-segmentation)
    add_subdirectory(app/seed-selector)
    add_subdirectory(app/grabcut)
    add_subdirectory(app/summary-flow)
endif()

if(${BUILD_TESTS})
    add_subdirectory(lab/test/coverage)
endif()


