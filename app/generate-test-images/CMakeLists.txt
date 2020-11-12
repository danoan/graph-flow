project(generate-test-images)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(generate-test-images
        main.cpp
        src/bean.cpp
        src/utils.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(generate-test-images graph-flow-utils graph-flow-core dipacus magLac)
else()
    add_dependencies(generate-test-images graph-flow-utils graph-flow-core)
endif()

target_include_directories(generate-test-images PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(generate-test-images
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-seedio
        -lgraph-flow-core
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS generate-test-images
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)