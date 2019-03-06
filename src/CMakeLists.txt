include("${CMAKE_CURRENT_LIST_DIR}/jadx/CMakeLists.txt")
include("${CMAKE_CURRENT_LIST_DIR}/java/CMakeLists.txt")


target_include_directories(jadxjni INTERFACE ${CMAKE_CURRENT_LIST_DIR})


target_sources(jadxjni
  INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/core.hpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils.hpp"
  INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/core.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/utils.cpp"
)

if(UNIX AND NOT APPLE) # Linux
  target_sources(jadxjni
    INTERFACE
      "${CMAKE_CURRENT_LIST_DIR}/jadx_prefix_linux.cpp"
  )
endif()

if(APPLE)
  target_sources(jadxjni
    INTERFACE
      "${CMAKE_CURRENT_LIST_DIR}/jadx_prefix_osx.cpp"
  )
endif()
