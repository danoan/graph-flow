project(shape-evolution-lib)

find_package(DGtal REQUIRED)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(shape-evolution-lib ${LIBRARY_ACTION}
        src/model/GraphContext.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(shape-evolution-lib graph-flow-utils graph-flow-core dipacus magLac)
else()
    add_dependencies(shape-evolution-lib graph-flow-utils graph-flow-core)
endif()

target_include_directories(shape-evolution-lib PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(shape-evolution-lib
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-core
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS shape-evolution-lib
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)