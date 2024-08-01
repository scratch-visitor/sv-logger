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

# export target inside install tree.
install(TARGETS logger
        EXPORT ${EXPORT_NAME}
        PUBLIC_HEADER DESTINATION "include/sv"
)
install(EXPORT ${EXPORT_NAME}
        NAMESPACE sv::
        DESTINATION "share/sv"
)

# ALIAS of target
add_library(sv::logger ALIAS logger)
