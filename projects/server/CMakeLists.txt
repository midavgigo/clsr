project(server VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../target")
set(SOURCE src/main.cpp src/net/SNetHandler/SNetHandler.cpp src/net/WorkThread/WorkThread.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} PUBLIC logger)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../logger/src"
)