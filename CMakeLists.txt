cmake_minimum_required(VERSION 3.21)
project(logger
  VERSION 0.1.0
  LANGUAGES CXX
)

if (NOT DEFINED CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
endif()

set(EXPORT_NAME sv-config-${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
elseif (UNIX)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
  find_package(Boost CONFIG REQUIRED)
else()
  find_package(Boost REQUIRED)
endif()

# build library
add_subdirectory(src)

# export target for using target in build tree(outside install tree).
export(TARGETS logger
      NAMESPACE sv::
      FILE ${EXPORT_NAME}.cmake
)

add_subdirectory(test)
