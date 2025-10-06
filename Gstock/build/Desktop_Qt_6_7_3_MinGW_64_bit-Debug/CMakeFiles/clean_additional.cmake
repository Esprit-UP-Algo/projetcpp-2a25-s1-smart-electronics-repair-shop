# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Gstock_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Gstock_autogen.dir\\ParseCache.txt"
  "Gstock_autogen"
  )
endif()
