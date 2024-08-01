cmake_minimum_required(VERSION 3.21)

add_library(logger INTERFACE
  sv/logger.hpp
)

set_target_properties(logger PROPERTIES
  PUBLIC_HEADER
    sv/logger.hpp
)

target_link_libraries(logger
  INTERFACE
    Boost::boost
)
