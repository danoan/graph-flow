project(test-coverage)

add_executable(test-coverage
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-digital.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-display.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-energy.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-image.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-string.cpp
${CMAKE_SOURCE_DIR}/modules/utils/test/src/test-timer.cpp
${CMAKE_SOURCE_DIR}/catch/catch.cpp)

target_compile_options(test-coverage PRIVATE
-O0
-g
--coverage
)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
        target_link_options(test-coverage PRIVATE --coverage)
else()
        target_link_libraries(coverage PRIVATE --coverage)
endif()

if (${USE_REMOTE_REPOSITORIES})
  add_dependencies(test-coverage dipacus graph-flow-utils)    
else()
  add_dependencies(test-coverage graph-flow-utils)    
endif ()


target_include_directories(test-coverage PRIVATE
        ${CMAKE_SOURCE_DIR}/catch
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(test-coverage
        -lgraph-flow-utils
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates    
        -lboost_filesystem    
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS test-coverage
        DESTINATION ${CMAKE_INSTALL_PREFIX}/test)