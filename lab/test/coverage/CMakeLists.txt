project(test-coverage)

add_executable(test-coverage
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-contour.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-misc.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-morphology.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-representation.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-set-operations.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-shapes.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/digital/test-transform.cpp
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
${CMAKE_SOURCE_DIR}/modules/contour-correction/src/model/graph/GraphModel.cpp
${CMAKE_SOURCE_DIR}/modules/contour-correction/src/model/image/GMM.cpp
${CMAKE_SOURCE_DIR}/modules/core/src/neighborhood/MorphologyNeighborhood.cpp
${CMAKE_SOURCE_DIR}/modules/core/src/neighborhood/RandomNeighborhood.cpp
${CMAKE_SOURCE_DIR}/modules/core/src/FlowGraph.cpp
${CMAKE_SOURCE_DIR}/modules/io/seed/src/GrabCutIO.cpp
${CMAKE_SOURCE_DIR}/modules/shape-evolution/src/model/GraphContext.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/types/BeanShape.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/types/Neighborhood.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/contour.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/misc.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/morphology.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/representation.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/set-operations.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/shapes.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/digital/transform.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/display.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/energy.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/image.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/string.cpp
${CMAKE_SOURCE_DIR}/modules/utils/src/timer.cpp
${CMAKE_SOURCE_DIR}/ext/catch/catch.cpp)

target_compile_options(test-coverage PRIVATE
-fprofile-arcs
-ftest-coverage
--coverage
)

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-coverage graph-flow-core graph-flow-io graph-flow-shape-evolution graph-flow-contour-correction graph-flow-utils)
else()
  add_dependencies(test-coverage graph-flow-core graph-flow-io graph-flow-shape-evolution graph-flow-contour-correction graph-flow-utils)
endif ()


target_include_directories(test-coverage PRIVATE
        ${CMAKE_SOURCE_DIR}/ext/catch
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/shape-evolution/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/contour-correction/include
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-coverage
        -lemon
        -lboost_filesystem
        -lboost_system
        -lpthread
        -lgcov
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-coverage
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)