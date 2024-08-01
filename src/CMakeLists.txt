cmake_minimum_required(VERSION 3.21)

add_library(${TARGET_NAME} INTERFACE
  sv/logger.hpp
)

set_target_properties(${TARGET_NAME} PROPERTIES
  PUBLIC_HEADER
    sv/logger.hpp
)

target_link_libraries(${TARGET_NAME}
  INTERFACE
    Boost::boost
)

install(TARGETS ${TARGET_NAME}
        EXPORT ${EXPORT_NAME}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_PREFIX}/include/sv"
)