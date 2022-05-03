add_library(utility)

target_sources(utility
  PRIVATE graph.cpp utilfunction.cpp
)
target_include_directories(utility
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)