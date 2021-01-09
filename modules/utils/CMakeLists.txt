project(graph-flow-utils)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-utils ${LIBRARY_ACTION}
        src/digital/morphology.cpp
        src/digital/representation.cpp
        src/digital/shapes.cpp        
        src/digital/contour.cpp
        src/digital/transform.cpp
        src/digital/set-operations.cpp
        src/digital/misc.cpp
        src/digital/types/BeanShape.cpp
        src/digital/types/Neighborhood.cpp
        src/energy.cpp
        src/display.cpp
        src/string.cpp
        src/image.cpp
        src/timer.cpp)

set_target_properties(graph-flow-utils PROPERTIES
        COMPILE_FLAGS -fPIC
        )

target_include_directories(graph-flow-utils PRIVATE
        include
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-utils
        -lgraph-flow-utils
        -lboost_system
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(DIRECTORY include
        DESTINATION ${CMAKE_INSTALL_PREFIX})

install(TARGETS graph-flow-utils
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

