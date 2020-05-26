cmake_minimum_required(VERSION 3.1)
cmake_policy(SET CMP0004 OLD)

set(GWORK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gwork)
add_subdirectory(${GWORK_DIR})

set(ROOTEX_INCLUDES
    ${ROOTEX_INCLUDES}
    ${GWORK_DIR}/source/platform/include
    ${GWORK_DIR}/source/gwork/include
    ${GWORK_DIR}/source/test/include
CACHE INTERNAL "")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${GWORK_DIR}/cmake/Modules/")

include_directories(${GWORK_DIR}/source/platform/include
                    ${GWORK_DIR}/source/gwork/include
                    ${GWORK_DIR}/source/test/include)
