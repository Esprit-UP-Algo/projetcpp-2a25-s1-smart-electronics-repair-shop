# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SmartMarket_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SmartMarket_autogen.dir\\ParseCache.txt"
  "SmartMarket_autogen"
  )
endif()
