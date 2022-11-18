
# OpenGL
list(APPEND LIB_TARGETS "d3d11.lib" "dxgi.lib" "d3dcompiler.lib")
list(APPEND LIB_INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS})

if(LIB_INCLUDE_DIRS)
	list(REMOVE_DUPLICATES LIB_INCLUDE_DIRS)
	target_include_directories(SYSTEM ${PROJ_NAME} PRIVATE ${LIB_INCLUDE_DIRS})
	if(MSVC)
		target_compile_options(${PROJ_NAME} PRIVATE
			"$<$<CXX_COMPILER_ID:Clang>:SHELL:-Xclang -isystem$<JOIN:${LIB_INCLUDE_DIRS}, -Xclang -isystem>>"
			"$<$<CXX_COMPILER_ID:MSVC>:SHELL:-experimental:external -external:W0 -external:anglebrackets -external:I$<JOIN:${LIB_INCLUDE_DIRS}, -external:I>>")
	else()
		target_compile_options(${PROJ_NAME} PRIVATE "SHELL:-isystem $<JOIN:${LIB_INCLUDE_DIRS}, -isystem>")
	endif()
endif()

target_link_libraries(${PROJ_NAME} PRIVATE ${LIB_TARGETS})
