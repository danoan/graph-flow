cmake_minimum_required(VERSION 3.10)
project(seed-selector)

add_executable(seed-selector seed-selector.cpp
        src/GUIControl.cpp
        src/GUIData.cpp
        src/InputData.cpp
        src/MaskSelector.cpp
        src/RectSelector.cpp)

add_dependencies(seed-selector graph-flow-utils)


target_include_directories(seed-selector PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(seed-selector
        -lgraph-flow-utils
        -lgraph-flow-utils
        -lboost_filesystem
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS seed-selector
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)


