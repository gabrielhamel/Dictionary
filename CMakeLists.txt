cmake_minimum_required(VERSION 3.10)

# Project name
project(Dictionary)

SET(SRC
    src/main.cpp
)

SET(INCLUDES
    includes
)

add_executable(dictionary
  ${SRC}
)

target_include_directories(dictionary PUBLIC
  ${INCLUDES}
)
