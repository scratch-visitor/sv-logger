cmake_minimum_required(VERSION 3.21)
project(tester
  LANGUAGES CXX
)

set(TESTER_NAME ${PROJECT_NAME})

add_executable(${TESTER_NAME}
  tester.cpp
)

target_include_directories(${TESTER_NAME}
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_link_libraries(${TESTER_NAME}
  PRIVATE
    Boost::boost
    sv::${TARGET_NAME}
)