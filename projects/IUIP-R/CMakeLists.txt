project(IUIP-R VERSION 0.1.0)
add_library(${PROJECT_NAME} src/Request.cpp src/Arg.cpp src/Request.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC logger)
target_include_directories(${PROJECT_NAME} PUBLIC                           
    "${PROJECT_BINARY_DIR}/src"
    "${PROJECT_SOURCE_DIR}/../logger/src"
)