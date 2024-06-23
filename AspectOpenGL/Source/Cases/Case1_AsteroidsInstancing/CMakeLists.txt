cmake_minimum_required(VERSION 3.0)

add_compile_definitions(UNICODE _UNICODE)
if (WIN7_SYSTEM_SUPPORT MATCHES ON)
    add_compile_definitions(_WIN32_WINNT=0x601)
endif()

# 向目标(库或可执行文件 添加编译选项)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 将当前目录源文件添加到DIR_SRCS
aux_source_directory(. DIR_SRCS)
# GLOB表示按照指定模式进行全局匹配，这里将当前目录头文件设置成HEADER_FILES
# 另，官方不推荐GLOB,而是显示将所有文件罗列出来...，因为只有运行cmake时才会自动添加，日常使用增添文件都无法被检测到
# 这里写好一个子项目后，基本不会更改，所以使用file(GLOB)
file(GLOB HEADER_FILES ./*.h)

# 添加现成静态库
link_directories("${CMAKE_SOURCE_DIR}/AspectOpenGL/Source/ThirdParty/freetype/lib")
link_directories("${CMAKE_SOURCE_DIR}/AspectOpenGL/Source/ThirdParty/irrKlang/lib")
if(WIN32)
  set(LIBS opengl32 freetype irrKlang)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif(WIN32)


# 添加现成动态库dll
# copy dlls


# 添加可执行文件并根据需求链接库
add_executable(Case1_AsteroidsInstancing WIN32 ${DIR_SRCS} ${HEADER_FILES})
target_link_libraries(Case1_AsteroidsInstancing
PUBLIC Glad
PUBLIC glm
PUBLIC stb
PUBLIC glfw
PUBLIC assimp
PUBLIC headers
PUBLIC ${LIBS}
)

# 设置链接器选项为/SUBSYSTEM:CONSOLE（对于MSVC）  
if(MSVC)  
    target_link_options(Case1_AsteroidsInstancing PRIVATE "/SUBSYSTEM:CONSOLE")  
endif()  

# copy shader files to build directory
file(GLOB SHADERS
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.vs"
    # "src/${chapter}/${demo}/*.frag"
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.fs"
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.tcs"
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.tes"
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.gs"
    "${SourceDir}/Cases/Case1_AsteroidsInstancing/*.cs"
 )
 foreach(SHADER ${SHADERS})
 if(WIN32)
    # configure_file(${SHADER} "test")
    add_custom_command(TARGET Case1_AsteroidsInstancing PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SHADER} $<TARGET_FILE_DIR:Case1_AsteroidsInstancing>)
 endif(WIN32)
 endforeach(SHADER)

#set_target_properties用于设置目标属性，也就是可执行文件或库的特性，例如链接器，编译器或安装路径等
set_target_properties(Case1_AsteroidsInstancing PROPERTIES OUTPUT_NAME "Case1_AsteroidsInstancing")

set_target_properties(Case1_AsteroidsInstancing PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(Case1_AsteroidsInstancing PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(Case1_AsteroidsInstancing PROPERTIES FOLDER "Demos")


