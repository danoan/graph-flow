project(random-seeds-app)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(random-seeds-app
        main.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(random-seeds-app dipacus graph-flow-seedio graph-flow-utils)
else()
    add_dependencies(random-seeds-app graph-flow-seedio graph-flow-utils)
endif()

target_include_directories(random-seeds-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${CMAKE_SOURCE_DIR}/modules/io/seed/include
        ${DIPACUS_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_libraries(random-seeds-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-seedio
        -lgraph-flow-utils
        -lboost_system
        -lboost_filesystem
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS random-seeds-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
