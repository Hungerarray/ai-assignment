cmake_minimum_required(VERSION 3.13)
project(AI_ASSIGNMENT)
set(CMAKE_CXX_STANDARD_REQUIRED 20) 

# add library
add_subdirectory(utility)

# make production
add_executable(production)
target_sources(production
  PRIVATE production.cpp
)

#  make bfs
add_executable(bfs)
target_sources(bfs
  PRIVATE bfs.cpp
)

# make greedy
add_executable(greedy)
target_sources(greedy
  PRIVATE greedy.cpp
)

# make astar
add_executable(astar)
target_sources(astar
  PRIVATE astar.cpp
)