cmake_minimum_required(VERSION 3.21)

file(GLOB_RECURSE HEADER_FILES
  RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
  *.hpp
)

message("HEADER_FILES: ${HEADER_FILES}")

add_library(${TARGET_NAME} INTERFACE)
add_library(sv::${TARGET_NAME} ALIAS ${TARGET_NAME})

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
  target_link_libraries(${TARGET_NAME}
    INTERFACE
      Boost::asio
      fmt::fmt-header-only
  )
else()
  target_link_libraries(${TARGET_NAME}
    INTERFACE
      fmt::fmt-header-only
  )
endif()

target_include_directories(${TARGET_NAME}
  INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

# export target inside install tree.
install(TARGETS ${TARGET_NAME}
        EXPORT ${PACKAGE_NAME}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sv
  DESTINATION include
  FILES_MATCHING
  PATTERN "*.hpp"
)

install(EXPORT ${PACKAGE_NAME}
        NAMESPACE sv::
        FILE ${EXPORT_NAME}.cmake
        DESTINATION "share/${PACKAGE_NAME}"
)

export(TARGETS ${TARGET_NAME}
      NAMESPACE sv::
      FILE ${EXPORT_NAME}.cmake
)
