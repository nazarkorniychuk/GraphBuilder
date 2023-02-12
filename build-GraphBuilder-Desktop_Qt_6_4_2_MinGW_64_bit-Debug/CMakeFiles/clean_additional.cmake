# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GraphBuilder_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GraphBuilder_autogen.dir\\ParseCache.txt"
  "GraphBuilder_autogen"
  )
endif()
