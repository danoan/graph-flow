project(grabcut-reweight-app)

find_package(DGtal REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(grabcut-reweight-app
        main.cpp
        src/grabcut.cpp
        src/GMM.cpp
        src/input/InputReader.cpp)

if(${USE_REMOTE_REPOSITORIES})
    add_dependencies(grabcut-reweight-app graph-flow-utils graph-flow-core dipacus magLac btools)
else()
    add_dependencies(grabcut-reweight-app graph-flow-utils graph-flow-core)
endif()

target_include_directories(grabcut-reweight-app PRIVATE
        include
        ${CMAKE_SOURCE_DIR}/modules/core/include
        ${CMAKE_SOURCE_DIR}/modules/utils/include
        ${DIPACUS_INCLUDE_DIRS}
        ${MAGLAC_INCLUDE_DIRS}
        ${DGTAL_INCLUDE_DIRS}
        ${BTOOLS_INCLUDE_DIRS}
        ${BOOST_INCLUDE_DIRS})

target_link_directories(grabcut-reweight-app PRIVATE
        ${CMAKE_BINARY_DIR}/modules/utils
        ${CMAKE_BINARY_DIR}/modules/core
        ${DIPACUS_LIBS_DIR}
        ${BTOOLS_LIBS_DIR}
        ${BOOST_LIBS_DIR})

target_link_libraries(grabcut-reweight-app
        -ldipacus-base
        -ldipacus-components
        -ldipacus-derivates
        -lgraph-flow-core
        -lgraph-flow-utils
        -lbtools-utils
        -lboost_filesystem
        -lpthread
        ${DGTAL_LIBRARIES}
        ${OpenCV_LIBS})

install(TARGETS grabcut-reweight-app
        DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

