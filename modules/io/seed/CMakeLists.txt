cmake_minimum_required(VERSION 3.2)
project(graph-flow-seedio)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-seedio ${LIBRARY_ACTION}
        src/GrabCutIO.cpp)

target_include_directories(graph-flow-seedio PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
	${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-seedio
        -lboost_system
        -lboost_filesystem
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-seedio
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
