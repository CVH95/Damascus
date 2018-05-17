# Test CMake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6.0)

# The name of the project
PROJECT(Cryptography)
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

include_directories( Blowfish/include RSA/include Security/include)

set(EXECUTABLE_OUTPUT_PATH "../bin")

# Create Blowfish shared library
add_library(Blowfish SHARED Blowfish/src/Blowfish.cpp)
# Create RSA shared library
add_library(RSA SHARED RSA/src/RSA.cpp)
# Create Security shared library
#add_library(Security SHARED Security/src/Security.cpp)

################
### BLOWFISH ###
################

# The executable to build:
ADD_EXECUTABLE(basicTestBF Blowfish/src/test.cpp)
TARGET_LINK_LIBRARIES(basicTestBF ${OPENSSL_LIBRARIES})

# The executable to build:
ADD_EXECUTABLE(BF_encryption Blowfish/src/encryption.cpp)
TARGET_LINK_LIBRARIES(BF_encryption Blowfish ${OPENSSL_LIBRARIES})

# The executable to build:
ADD_EXECUTABLE(BF_decryption Blowfish/src/decryption.cpp)
TARGET_LINK_LIBRARIES(BF_decryption Blowfish ${OPENSSL_LIBRARIES})

#################
###    RSA    ###
#################

# The executable to build:
ADD_EXECUTABLE(basicTestRSA RSA/src/test.cpp)
TARGET_LINK_LIBRARIES(basicTestRSA RSA)

# The executable to build:
ADD_EXECUTABLE(randomKey RSA/src/generate_key.cpp)
TARGET_LINK_LIBRARIES(randomKey RSA)

# The executable to build:
ADD_EXECUTABLE(encryptionRSA RSA/src/encrypt.cpp)
TARGET_LINK_LIBRARIES(encryptionRSA RSA)

# The executable to build:
ADD_EXECUTABLE(decryptionRSA RSA/src/decrypt.cpp)
TARGET_LINK_LIBRARIES(decryptionRSA RSA)


# Output end message
MESSAGE(${PROJECT_NAME} " done!")
