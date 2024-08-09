cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE HEADER_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  *.hpp
)

message("HEADER_FILES: ${HEADER_FILES}")

add_library(${PACKAGE_NAME} INTERFACE)
add_library(sv::${TARGET_NAME} ALIAS ${PACKAGE_NAME})

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
  target_link_libraries(${PACKAGE_NAME}
    INTERFACE
      Boost::asio
      fmt::fmt-header-only
  )
else()
  target_link_libraries(${PACKAGE_NAME}
    INTERFACE
      fmt::fmt-header-only
  )
endif()

target_include_directories(${PACKAGE_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# export target inside install tree.
install(TARGETS ${PACKAGE_NAME}
        EXPORT ${EXPORT_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sv
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)

install(EXPORT ${EXPORT_NAME}
        NAMESPACE sv::
        COMPONENT ${TARGET_NAME}
        DESTINATION "share/${PACKAGE_NAME}"
)

export(TARGETS ${PACKAGE_NAME}
      NAMESPACE sv::
      FILE ${EXPORT_NAME}.cmake
)
