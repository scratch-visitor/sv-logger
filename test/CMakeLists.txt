cmake_minimum_required(VERSION 3.21)
project(${PACKAGE_NAME}-tester CXX)

add_executable(${PROJECT_NAME} tester.cpp)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    sv::${TARGET_NAME}
)