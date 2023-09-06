cmake_minimum_required(VERSION 3.26)
project(three_bands_filter_bank)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

if (MSVC)
    add_compile_options(/wd4244)
endif ()

include_directories(src extra)
list(APPEND SRC_FILES main.cpp)
aux_source_directory(src SRC_FILES)

add_executable(${PROJECT_NAME} ${SRC_FILES})
