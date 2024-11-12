project(server VERSION 0.1.0)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../../target")
set(SOURCE src/main.cpp src/net/SNetHandler/SNetHandler.cpp src/net/WorkThread/WorkThread.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC logger IUIP PRIVATE Threads::Threads)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../logger/src"
    "${PROJECT_SOURCE_DIR}/../IUIP/src"
)