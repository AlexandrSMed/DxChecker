# =======================================================#
# Project Settings
# =======================================================#

cmake_minimum_required(VERSION 3.23)
set(PROJ_NAME DxChecker)
project(${PROJ_NAME} CXX)
list(APPEND CMAKE_MODULE_PATH
    "${CMAKE_SOURCE_DIR}/cmakescripts"
    "${CMAKE_SOURCE_DIR}/secure")

# =======================================================#
# Source Files Settings
# =======================================================#

list(APPEND SOURCE_FILES
    src/main.cpp
    src/DXUtils.cpp
    src/FSUtils.cpp)
add_executable(${PROJ_NAME} ${SOURCE_FILES})
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

target_compile_definitions(${PROJ_NAME} PRIVATE NOMINMAX)
target_compile_options(${PROJ_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:-Zc:__cplusplus -W4>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall
        -Wno-c++98-compat
        -Wno-c++98-compat-pedantic
        -Wno-missing-prototypes
        -Wno-nonportable-system-include-path>)
target_include_directories(${PROJ_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src/")

# =======================================================#
# Windows Code Signing
# =======================================================#

if (SHOULD_SIGN)
    if (WIN32)
        include(SigningVariablesWindows)
        include(CodeSignWindows)
        code_sign_windows(${PROJ_NAME}
        "DxCheck is a minimalistic tool to explore supported Direct3D versions on your machine"
        https://github.com/AlexandrSMed/DxChecker
        ${PFX_PATH} ${PFX_PASSPHRASE})
    endif()
    # TODO: implement code sign for other platforms
endif()

#TODO: unit testing