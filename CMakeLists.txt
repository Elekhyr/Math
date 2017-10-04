cmake_minimum_required(VERSION 3.2)
project(Math)
 add_compile_options(-std=c++0x)
file(GLOB MATH_SRC
    "Include/*.hpp"
    "Source/*.cpp"
)

if(WIN32)
	set(SUFFX ".lib")
	set(PREFX "")
else()
	set(SUFFX ".a")
	set(PREFX "lib")
endif(WIN32)

set(CMAKE_DEBUG_POSTFIX "_d")
add_library(Math ${MATH_SRC})
target_include_directories(Math PUBLIC "Include")

set_target_properties(Math
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Lib"
	PREFIX "${PREFX}"
	SUFFIX "${SUFFX}"
)