ExternalProject_Add(scabolic
        GIT_REPOSITORY https://github.com/danoan/SCaBOliC.git
        GIT_TAG elastica-potential
        SOURCE_DIR ${EXTPROJECTS_SOURCE_DIR}/SCaBOliC
        CMAKE_ARGS
        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_INSTALL_PREFIX=${EXTPROJECTS_BUILD_DIR}
        -DUSE_REMOTE_REPOSITORIES=OFF
        -DDIPACUS_INCLUDE_DIRS=${EXTPROJECTS_BUILD_DIR}/include
        -DDIPACUS_LIBS_DIR=${EXTPROJECTS_BUILD_DIR}/lib
        -DGEOC_INCLUDE_DIRS=${EXTPROJECTS_BUILD_DIR}/include
        -DBOOST_LIBS_DIR=${BOOST_LIBS_DIR}
        -DCREATE_SHARED_LIBRARIES=ON)

add_dependencies(scabolic dipacus geoc)