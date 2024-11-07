project(test VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../target")
set(SOURCE src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} PUBLIC logger IUIP-R)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../logger/src"
    "${PROJECT_SOURCE_DIR}/../IUIP-R/src"
)