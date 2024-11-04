project(logger VERSION 0.1.0)
message(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
add_library(${PROJECT_NAME} src/logger.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})