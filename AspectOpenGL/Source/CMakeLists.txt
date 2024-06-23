set(ThirdPartyDir "${SourceDir}/ThirdParty")

add_subdirectory("Breakout")
add_subdirectory("ThirdParty")
add_subdirectory("Cases")

# you maybe need assets file and want to copy it to cmake binary dir
#if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Texture)
	#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Texture DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#endif()