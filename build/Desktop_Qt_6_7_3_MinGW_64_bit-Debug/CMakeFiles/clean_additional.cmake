# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\repairshop_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\repairshop_autogen.dir\\ParseCache.txt"
  "repairshop_autogen"
  )
endif()
