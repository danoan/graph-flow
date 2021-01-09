cmake_minimum_required(VERSION 3.10)
project(summary-flow)

add_executable(summary-flow
        summary-flow.cpp
        src/control/OneImageFlow.cpp
        src/input/InputReader.cpp
        src/model/ColorScheme.cpp
        src/model/DrawingBuffer.cpp
        src/utils.cpp
        )

if(${USE_REMOTE_REPOSITORIES})
        add_dependencies(summary-flow graph-flow-utils)
endif()

target_compile_features(summary-flow PRIVATE cxx_auto_type)
target_compile_options(summary-flow PRIVATE -fext-numeric-literals)

target_include_directories(summary-flow PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        )

target_link_libraries(summary-flow
        -lgraph-flow-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS summary-flow
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
