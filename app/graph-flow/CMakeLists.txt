project(graph-flow-app)

find_package(DGtal REQUIRED)

add_executable(graph-flow-app
src/input/InputReader.cpp
src/utils.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-app shape-evolution-lib dipacus magLac)
else()
    add_dependencies(graph-flow-app shape-evolution-lib)
endif()

target_include_directories(graph-flow-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/shape-evolution/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-core
        -lgraph-flow-utils
        -lshape-evolution-lib
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS graph-flow-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)