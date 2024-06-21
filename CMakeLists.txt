cmake_minimum_required (VERSION 3.0)

project(CppDaydaydream)

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

# find the required packages,if cmake find the packages,you can use message to print,you use their explicit variables after find_package
#find_package(GLM REQUIRED)
#message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")
#find_package(GLFW3 REQUIRED)
#message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
#find_package(ASSIMP REQUIRED)
#message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
# find_package(SOIL REQUIRED)
# message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
# find_package(GLEW REQUIRED)
# message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")

# for different platform




# TODO third party libs
#add_subdirectory("ImGui")
#set_target_properties(ImGui PROPERTIES FOLDER "ImGui")

# add sub project directories
add_subdirectory("Core")
# different knowledge points, this project is divided into four main contents.
# maybe update other contents in the future...
add_subdirectory("CppDaydaydream") # 1.cpp_basic_things
add_subdirectory("Wheels") # 2.stl_data_structures_wheels
add_subdirectory("ProjectThings") # 3.project_things, project building problem or something like this
add_subdirectory("Algorithms") # 4.algorithms, mainly solve general algorithm about gaming or novel technics that could be used in gaming here

# maybe you need set sub-projs to a specific variable
#set(POINTS
    #1.cpp_basic_things
    #2.stl_data_structures
    #3.project_things
    #4.algorithms
#)
# maybe add other folders later...




