project(test-graph-flow-utils)

add_executable(test-graph-flow-utils 
src/test-digital.cpp
src/test-display.cpp
src/test-energy.cpp
src/test-image.cpp
src/test-string.cpp
src/test-timer.cpp
test-graph-flow-utils.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-graph-flow-utils dipacus graph-flow-utils)    
else()
  add_dependencies(test-graph-flow-utils graph-flow-utils)    
endif ()


target_include_directories(test-graph-flow-utils PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-graph-flow-utils
        -lgraph-flow-utils
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-graph-flow-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)