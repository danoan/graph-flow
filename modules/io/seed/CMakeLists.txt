cmake_minimum_required(VERSION 3.2)
project(graph-flow-io)

if(${BUILD_TESTS})
    add_subdirectory(test)
endif()

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-io ${LIBRARY_ACTION}
        src/GrabCutIO.cpp)

target_include_directories(graph-flow-io PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
	${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-io
        -lboost_system
        -lboost_filesystem
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-io
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
