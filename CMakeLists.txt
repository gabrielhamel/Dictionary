cmake_minimum_required(VERSION 3.10)

# Project name
project(Dictionary LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# Conan
include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

SET(SRC
  tests/main.cpp
  tests/Substitution.cpp
  tests/RemovedChar.cpp
  tests/AddedChar.cpp
  tests/Equal.cpp
  tests/Mixed.cpp
)

SET(INCLUDES
  includes
)

add_executable(unit-tests
  ${SRC}
)

target_include_directories(unit-tests PUBLIC
  ${INCLUDES}
)

target_link_libraries(unit-tests PRIVATE ${CONAN_LIBS})
target_link_libraries(unit-tests PRIVATE ${CMAKE_DL_LIBS})

ENABLE_TESTING()
ADD_TEST(tests bin/unit-tests)
