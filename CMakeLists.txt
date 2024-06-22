cmake_minimum_required (VERSION 3.0)

project(OpenGLDeck)

# cmake settings
include(FetchContent)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT SET_UP_CONFIGURATIONS_DONE)
    set(SET_UP_CONFIGURATIONS_DONE TRUE)

    # No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator
    # Also no reason mess with CMAKE_BUILD_TYPE if it's a multiconfig generator.
    get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    if(isMultiConfig)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE) 
    else()
        if(NOT CMAKE_BUILD_TYPE)
            message("Defaulting to release build.")
            set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
        endif()
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY HELPSTRING "Choose the type of build")
        # set the valid options for cmake-gui drop-down list
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;Profile")
    endif()
    # now set up the Profile configuration
    set(CMAKE_C_FLAGS_PROFILE "...")
    set(CMAKE_CXX_FLAGS_PROFILE "...")
    set(CMAKE_EXE_LINKER_FLAGS_PROFILE "...")
endif()

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(DeckRootDir "${CMAKE_CURRENT_SOURCE_DIR}")

# to be fixed, temporary root dir config
#configure_file(configuration/root_directory.h.in configuration/root_directory.h)
#include_directories(${CMAKE_BINARY_DIR}/configuration)
# add sub project directories
add_subdirectory("AspectOpenGL")
# different knowledge points, this project is divided into four main contents.
# maybe update other contents in the future...
# maybe you need set sub-projs to a specific variable
#set(POINTS
    #1.cpp_basic_things
    #2.stl_data_structures
    #3.project_things
    #4.algorithms
#)



