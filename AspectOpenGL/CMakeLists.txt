set(SourceDir "${DeckRootDir}/AspectOpenGL/Source")

add_subdirectory("Source")

# you maybe need assets file and want to copy it to cmake binary dir
#if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Texture)
	#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Texture DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#endif()