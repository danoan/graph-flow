project(graph-flow-shape-evolution)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-shape-evolution ${LIBRARY_ACTION}
        src/model/GraphContext.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-shape-evolution graph-flow-utils graph-flow-core magLac)
else()
    add_dependencies(graph-flow-shape-evolution graph-flow-utils graph-flow-core)
endif()

target_include_directories(graph-flow-shape-evolution PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-shape-evolution
        -lgraph-flow-utils
        -lgraph-flow-core
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-shape-evolution
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)