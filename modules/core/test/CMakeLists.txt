project(test-graph-flow-core)

add_executable(test-graph-flow-core
src/test-morphology.cpp
src/test-FlowGraph.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-graph-flow-core dipacus graph-flow-core graph-flow-utils)    
else()
  add_dependencies(test-graph-flow-core graph-flow-core graph-flow-utils)    
endif ()


target_include_directories(test-graph-flow-core PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-graph-flow-core
        -lgraph-flow-core
        -lgraph-flow-utils
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-graph-flow-core
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)