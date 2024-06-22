set(LearnOpenGLDir ${ThirdPartyDir}/learnopengl)

file(GLOB HEADER_FILES ${LearnOpenGLDir}/*.h)
add_library(learnopengl ${HEADER_FILES})
target_include_directories(learnopengl INTERFACE ${LearnOpenGLDir})