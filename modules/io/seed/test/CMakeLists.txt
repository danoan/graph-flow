project(test-graph-flow-io)

add_executable(test-graph-flow-io
src/test-GrabCutIO.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-graph-flow-io dipacus graph-flow-io)    
else()
  add_dependencies(test-graph-flow-io graph-flow-io)    
endif ()


target_include_directories(test-graph-flow-io PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-graph-flow-io
        -lgraph-flow-io
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-graph-flow-io
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)