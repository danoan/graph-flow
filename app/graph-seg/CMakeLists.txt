project(graph-seg-app)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(graph-seg-app
        src/input/InputReader.cpp
        src/utils.cpp
        src/model/graph/GraphModel.cpp
        src/model/image/GMM.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-seg-app graph-flow-utils graph-flow-core graph-flow-io dipacus magLac)
else()
    add_dependencies(graph-seg-app graph-flow-utils graph-flow-core graph-flow-io)
endif()

target_include_directories(graph-seg-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-seg-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-io
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS graph-seg-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)