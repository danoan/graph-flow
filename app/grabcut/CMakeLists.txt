cmake_minimum_required(VERSION 3.10)
project(grabcut)

add_executable(grabcut GrabCut.cpp src/InputData.cpp src/GrabCutApplication.cpp)
add_dependencies(grabcut graph-flow-io graph-flow-utils)

target_include_directories(grabcut PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRECTORIES})

target_link_libraries(grabcut
        -lgraph-flow-io
        -lgraph-flow-utils
        -ldipacus-components
        -ldipacus-base
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS grabcut
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
