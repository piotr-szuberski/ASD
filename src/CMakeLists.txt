# if there will be a library added, then
# target_include_directories(<library_name> PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/<path_to_headers)
# it will add a library and include path (-I flag) for needed headers

# it will add compiler flags to the library, visible as constants, e.g LIB_VERSION=2
#target_compile_definitions(<library_name> PUBLIC <SOME_NAME>=<VALUE>)

include_directories(${CMAKE_SOURCE_DIR}/src)