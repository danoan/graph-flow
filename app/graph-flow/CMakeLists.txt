project(graph-flow-app)

find_package(DGtal REQUIRED)

add_executable(graph-flow-app
        src/input/InputReader.cpp
        src/utils.cpp
        src/graph-flow.cpp
        src/model/StandardModel.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-app graph-flow-utils graph-flow-core dipacus magLac btools)
else()
    add_dependencies(graph-flow-app graph-flow-utils graph-flow-core)
endif()

target_include_directories(graph-flow-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_directories(graph-flow-app PRIVATE
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${DIPACUS_LIBS_DIR}
        ${BTOOLS_LIBS_DIR}
        ${BOOST_LIBS_DIR})

target_link_libraries(graph-flow-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lbtools-utils
        -lgraph-flow-core
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS graph-flow-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)