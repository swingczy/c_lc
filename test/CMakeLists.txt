project(c_lc_test)
add_executable(${PROJECT_NAME} main_test.c)
include_directories(${PROJECT_SOURCE_DIR}/../inc)
target_link_libraries(${PROJECT_NAME} m lc)

add_test(NAME ${PROJECT_NAME}
         COMMAND ${PROJECT_NAME})
