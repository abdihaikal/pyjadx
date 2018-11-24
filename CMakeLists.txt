
cmake_minimum_required(VERSION 3.6)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")
set(THIRD_PARTY_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/third-party/")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git" AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/.git")
  find_package(Git REQUIRED)

  # Information from git
  # ====================
  include(GitInfo)
else()
  set(PYJADX_VERSION_MAJOR "0")
  set(PYJADX_VERSION_MINOR "0")
  set(PYJADX_VERSION_PATCH "0")
endif()


configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in"
  "${CMAKE_CURRENT_BINARY_DIR}/version.h"
)

# Pyjadx Project
# ============
project(PYJADX VERSION ${PYJADX_VERSION_MAJOR}.${PYJADX_VERSION_MINOR}.${PYJADX_VERSION_PATCH})
message(STATUS "${PROJECT_NAME} ${PROJECT_VERSION}")



# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Install path prefix prepended on to install directories." FORCE)
endif()



find_package(JNI REQUIRED)
add_library(jadxjni INTERFACE)

include("${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt")

target_include_directories(jadxjni INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${JNI_INCLUDE_DIRS}
  ${THIRD_PARTY_DIRECTORY}/jni.hpp-4.0.0/include
)
target_link_libraries(jadxjni INTERFACE ${JNI_LIBRARIES})
target_compile_features(jadxjni INTERFACE cxx_std_17)


#add_executable(poc "poc.cpp")
#
#set_target_properties(poc PROPERTIES POSITION_INDEPENDENT_CODE ON)
#set_target_properties(poc PROPERTIES LINK_WHAT_YOU_USE ON)
#
#target_link_libraries(poc PUBLIC jadxjni)

add_subdirectory(bindings)

