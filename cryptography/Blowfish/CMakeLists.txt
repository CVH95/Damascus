# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT(Blowfish)
MESSAGE(${PROJECT_NAME} ":")

# Set build type to release
SET(CMAKE_BUILD_TYPE Release)
MESSAGE("-- Build type: " ${CMAKE_BUILD_TYPE})

# Find Required OpenSSL packages
find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIRS})
  #target_link_libraries (${PROJECT_NAME} ${OPENSSL_LIBRARIES})
  #target_link_libraries (devicehub ${OPENSSL_LIBRARIES})
endif(OPENSSL_FOUND)

include_directories( include )

set(EXECUTABLE_OUTPUT_PATH "../bin")

# Create shared library
add_library(Blowfish SHARED src/Blowfish.cpp)

# The executable to build:
ADD_EXECUTABLE(basicTest src/test.cpp)
TARGET_LINK_LIBRARIES(basicTest ${OPENSSL_LIBRARIES})

# The executable to build:
ADD_EXECUTABLE(BF_encryption src/encryption.cpp)
TARGET_LINK_LIBRARIES(BF_encryption Blowfish ${OPENSSL_LIBRARIES})

# The executable to build:
ADD_EXECUTABLE(BF_decryption src/decryption.cpp)
TARGET_LINK_LIBRARIES(BF_decryption Blowfish ${OPENSSL_LIBRARIES})

# Output end message
MESSAGE(${PROJECT_NAME} " done!")
