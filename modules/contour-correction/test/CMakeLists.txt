project(test-graph-flow-contour-correction)

add_executable(test-graph-flow-contour-correction
src/test-graphFlow.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-graph-flow-contour-correction dipacus graph-flow-core graph-flow-contour-correction graph-flow-utils)    
else()
  add_dependencies(test-graph-flow-contour-correction graph-flow-core graph-flow-contour-correction graph-flow-utils)    
endif ()


target_include_directories(test-graph-flow-contour-correction PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/contour-correction/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-graph-flow-contour-correction
        -lgraph-flow-contour-correction
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-io
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-graph-flow-contour-correction
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)