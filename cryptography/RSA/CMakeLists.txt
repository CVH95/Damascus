# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT(RSA)
MESSAGE(${PROJECT_NAME} ":")

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

# Include directories
INCLUDE_DIRECTORIES( include )

set(EXECUTABLE_OUTPUT_PATH "../bin")

# Create shared library
add_library(RSA SHARED src/RSA.cpp)

# The shared library to build:
ADD_EXECUTABLE(basicTest src/test.cpp)
TARGET_LINK_LIBRARIES(basicTest RSA ${ROBWORK_LIBRARIES})

# Output end message
MESSAGE(${PROJECT_NAME} " done!")
