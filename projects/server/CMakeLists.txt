project(server VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../target")
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC logger)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/../logger/src"
)