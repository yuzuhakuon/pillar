set(app_name "hello")

add_executable(${app_name} main.cc)
target_link_libraries(${app_name} PRIVATE pillar)
target_include_directories(${app_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(
  ${app_name}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../${ARTICRAFT_OUT}")
