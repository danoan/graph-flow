project(gf-contour-correction)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(gf-contour-correction
        src/input/InputReader.cpp
        src/utils.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(gf-contour-correction graph-flow-utils graph-flow-core graph-flow-io graph-flow-contour-correction magLac)
else()
    add_dependencies(gf-contour-correction graph-flow-utils graph-flow-core graph-flow-io graph-flow-contour-correction)
endif()

target_include_directories(gf-contour-correction PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${CMAKE_SOURCE_DIR}/modules/contour-correction/include
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(gf-contour-correction
        -lgraph-flow-utils
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-io
        -lgraph-flow-contour-correction
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS gf-contour-correction
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)