cmake_minimum_required(VERSION 3.21)
project(tester
  LANGUAGES CXX
)

add_executable(${PROJECT_NAME}
  tester.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Boost::asio
    sv-logger
)