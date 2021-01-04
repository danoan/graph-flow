project(test-coverage)

add_executable(test-coverage
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-digital.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-display.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-energy.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-image.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-string.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-timer.cpp
${CMAKE_SOURCE_DIR}/modules/shape-evolution/test/src/test-graphFlow.cpp
${CMAKE_SOURCE_DIR}/modules/io/seed/test/src/test-GrabCutIO.cpp
${CMAKE_SOURCE_DIR}/modules/core/test/src/test-FlowGraph.cpp
${CMAKE_SOURCE_DIR}/modules/core/test/src/test-morphology.cpp
${CMAKE_SOURCE_DIR}/modules/contour-correction/test/src/test-graphFlow.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

target_compile_options(test-coverage PRIVATE
-fprofile-arcs
-ftest-coverage
--coverage
)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-coverage dipacus graph-flow-core graph-flow-io graph-flow-shape-evolution graph-flow-contour-correction graph-flow-utils)    
else()
  add_dependencies(test-coverage graph-flow-core graph-flow-io graph-flow-shape-evolution graph-flow-contour-correction graph-flow-utils)    
endif ()


target_include_directories(test-coverage PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/shape-evolution/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/contour-correction/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-coverage
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-io
        -lgraph-flow-shape-evolution
        -lgraph-flow-contour-correction
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lemon
        -lboost_filesystem    
        -lboost_system
        -lpthread
        -lgcov
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-coverage
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)