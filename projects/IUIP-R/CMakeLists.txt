project(IUIP-R VERSION 0.1.0)
add_library(${PROJECT_NAME} src/Request.cpp src/Arg.cpp src/Request.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})