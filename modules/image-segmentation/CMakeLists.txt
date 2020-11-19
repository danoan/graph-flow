project(graph-flow-image-segmentation)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

set(LIBRARY_ACTION "STATIC")
if(${CREATE_SHARED_LIBRARIES})
    set(LIBRARY_ACTION "SHARED")
endif()

add_library(graph-flow-image-segmentation ${LIBRARY_ACTION}
        src/model/graph/GraphModel.cpp
        src/model/image/GMM.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(graph-flow-image-segmentation graph-flow-utils graph-flow-core graph-flow-io dipacus magLac)
else()
    add_dependencies(graph-flow-image-segmentation graph-flow-utils graph-flow-core graph-flow-io)
endif()

target_include_directories(graph-flow-image-segmentation PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(graph-flow-image-segmentation
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-core
        -lgraph-flow-utils
        -lgraph-flow-io
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS graph-flow-image-segmentation
        DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)