project(test-graph-flow-shape-evolution)

add_executable(test-graph-flow-shape-evolution
src/test-graphFlow.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-graph-flow-shape-evolution dipacus graph-flow-core graph-flow-shape-evolution graph-flow-utils)    
else()
  add_dependencies(test-graph-flow-shape-evolution graph-flow-core graph-flow-shape-evolution graph-flow-utils)    
endif ()


target_include_directories(test-graph-flow-shape-evolution PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/shape-evolution/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-graph-flow-shape-evolution
        -lgraph-flow-shape-evolution
        -lgraph-flow-core
        -lgraph-flow-utils
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-graph-flow-shape-evolution
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)