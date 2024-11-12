project(client VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../target")
set(SOURCE src/main.cpp src/CNetHandler/CNetHandler.cpp)
set(CLIENT_INTERFACE CLI)
set(CONNECT_ADDRESS "127.0.0.1")
set(CONNECT_PORT 5000)
configure_file("src/client_config.h.in" "src/client_config.h" @ONLY)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(${PROJECT_NAME} PUBLIC logger IUIP)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../logger/src"
    "${PROJECT_SOURCE_DIR}/../IUIP/src"
)