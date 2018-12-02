cmake_minimum_required(VERSION 3.1)
include(ExternalProject)

set(PYBIND11_VERSION 2.2.3)
set(PYBIND11_SHA256 SHA256=3a3b7b651afab1c5ba557f4c37d785a522b8030dfc765da26adc2ecd1de940ea)
set(PYBIND11_URL "${THIRD_PARTY_DIRECTORY}/pybind11-${PYBIND11_VERSION}.tar.gz" CACHE STRING "URL to the Pybind11 repo")
ExternalProject_Add(pybind11
  URL               ${PYBIND11_URL}
  URL_HASH          ${PYBIND11_SHA256}
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   "")
ExternalProject_get_property(pybind11 SOURCE_DIR)
set(PYBIND11_SOURCE_DIR "${SOURCE_DIR}")

# Add a CMake parameter for choosing a desired Python version
if(NOT JADX_PYTHON_VERSION)
  set(JADX_PYTHON_VERSION "" CACHE STRING "Python version to use for compiling modules")
endif()

set(Python_ADDITIONAL_VERSIONS 3.7 3.6 3.5 3.4)
find_package(PythonLibsNew ${JADX_PYTHON_VERSION} REQUIRED)

set(JADX_PYTHON_SRC
  pyjadx.cpp
)

add_library(pyjadx SHARED ${JADX_PYTHON_SRC})

target_include_directories(pyjadx PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/"
  "${PYTHON_INCLUDE_DIR}"
  "${PYBIND11_SOURCE_DIR}/include")


add_dependencies(pyjadx pybind11)

target_link_libraries(pyjadx PUBLIC jadxjni)

set_target_properties(pyjadx PROPERTIES PREFIX "")

if(APPLE)
  set_target_properties(pyjadx PROPERTIES MACOSX_RPATH ".")
  set_target_properties(pyjadx PROPERTIES LINK_FLAGS "-undefined dynamic_lookup ")
endif()

if (UNIX)
  set_target_properties(pyjadx PROPERTIES SUFFIX ".so")
elseif(WIN32)
  set_target_properties(pyjadx PROPERTIES SUFFIX ".pyd")
endif()
