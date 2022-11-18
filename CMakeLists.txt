#CMakeLists.txt

# =======================================================#
# Project Settings
# =======================================================#

cmake_minimum_required(VERSION 3.23)
set(PROJ_NAME DxChecker)
project(${PROJ_NAME})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmakescripts")


# =======================================================#
# Source Files Settings
# =======================================================#

list(APPEND SOURCE_FILES
    src/main.cpp)
add_executable(${PROJ_NAME} ${SOURCE_FILES} "src/DXUtils.h" "src/GPUDescriptor.h" "src/DXUtils.cpp" "src/FSUtils.h" "src/FSUtils.cpp")
set_property(TARGET ${PROJ_NAME} PROPERTY CXX_STANDARD 17)

if (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJ_NAME})
endif()


# =======================================================#
# Library depdendencies
# =======================================================#

add_subdirectory(libs)

# =======================================================#
# Compiler Settings
# =======================================================#

target_compile_options(${PROJ_NAME} PRIVATE  -DLOG
    $<$<CXX_COMPILER_ID:MSVC>:-Zc:__cplusplus -W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wno-c++98-compat -Wno-missing-prototypes>
)
target_include_directories(${PROJ_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/src/")

# =======================================================#
# Windows Code Signing
# =======================================================#

if (SHOULD_SIGN)
    if (WIN32)
        include(${CMAKE_CURRENT_SOURCE_DIR}/secure/CodeSignWindows.cmake)
        code_sign_windows(${PROJ_NAME})
    endif()
    # TODO: implement code sign for other platforms
endif()