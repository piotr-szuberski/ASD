function(SetDefaultBuildType defaultBuildType)


  # https://blog.kitware.com/cmake-and-the-default-build-type/`
  if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${defaultBuildType}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${defaultBuildType}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
      "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
  endif()
endfunction()
