project(graph-flow-core)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()


add_library(graph-flow-core ${LIBRARY_ACTION}
        src/graph-flow/core/FlowGraph.cpp
        src/graph-flow/core/neighborhood/MorphologyNeighborhood.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-core graph-flow-utils dipacus geoc)
else()
    add_dependencies(graph-flow-core graph-flow-utils)
endif()

set_target_properties(graph-flow-core PROPERTIES
        COMPILE_FLAGS -fPIC
        )

target_include_directories(graph-flow-core PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS})

target_link_libraries(graph-flow-core
        -ldipacus-base
        -lgraph-flow-utils
        -lboost_system
        -lemon
        ${DGTAL_LIBRARIES})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-core
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)