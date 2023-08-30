cmake_minimum_required(VERSION 3.0.0)
project(c_lc VERSION 0.1.0 LANGUAGES C)

include_directories(inc)
add_executable(main src/main.c)
add_library(lc STATIC src/lc_app.c)

option(BUILD_TEST "Whether or not to build the tests" ON)
if (${BUILD_TEST})
    message(STATUS "Building tests")
    enable_testing()
    add_subdirectory(test)
    include(CTest)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(lc m)
target_link_libraries(main lc)
