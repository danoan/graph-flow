project(graph-seg-app)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(graph-seg-app
        src/input/InputReader.cpp
        src/utils/utils.cpp
        src/utils/data-term.cpp
        src/graph-seg.cpp
        src/model/graph/GraphContext.cpp
        src/model/graph/GraphModel.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-seg-app graph-flow-utils graph-flow-core dipacus magLac btools)
else()
    add_dependencies(graph-seg-app graph-flow-utils graph-flow-core)
endif()

target_include_directories(graph-seg-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-seg-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lbtools-seedio
        -lbtools-utils
        -lgraph-flow-core
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS graph-seg-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)