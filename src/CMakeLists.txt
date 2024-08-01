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

# export target inside install tree.
install(TARGETS ${TARGET_NAME}
        EXPORT ${EXPORT_NAME}
        PUBLIC_HEADER DESTINATION "include/sv"
)
install(EXPORT ${EXPORT_NAME}
        NAMESPACE sv::
        DESTINATION "share/${PACKAGE_NAME}"
)

# ALIAS of target
add_library(sv::${TARGET_NAME} ALIAS ${TARGET_NAME})
