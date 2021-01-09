project(gf-shape-evolution)

find_package(DGtal REQUIRED)

add_executable(gf-shape-evolution
src/input/InputReader.cpp
src/utils.cpp
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(gf-shape-evolution graph-flow-utils graph-flow-shape-evolution magLac)
else()
    add_dependencies(gf-shape-evolution graph-flow-utils graph-flow-shape-evolution)
endif()

target_include_directories(gf-shape-evolution PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/shape-evolution/include
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(gf-shape-evolution
        -lgraph-flow-utils
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-shape-evolution
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS gf-shape-evolution
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)