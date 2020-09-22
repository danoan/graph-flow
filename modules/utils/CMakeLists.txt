project(graph-flow-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-utils ${LIBRARY_ACTION}
        src/timer.cpp
        src/digital.cpp
        src/energy.cpp
        src/display.cpp
        src/string.cpp
        src/ring.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-utils dipacus geoc)
endif()

set_target_properties(graph-flow-utils PROPERTIES
        COMPILE_FLAGS -fPIC
        )

target_include_directories(graph-flow-utils PRIVATE
        include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-utils
        -ldipacus-base
        -ldipacus-components
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

