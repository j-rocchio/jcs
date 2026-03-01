cmake_minimum_required(VERSION 3.10)
project(jcs LANGUAGES C VERSION 0.0.0)
set(CMAKE_C_STANDARD 23)

add_subdirectory(json-c EXCLUDE_FROM_ALL)

file(GLOB JCS_SOURCES "src/*.c")
add_library(jcs_shared SHARED ${JCS_SOURCES})
set_target_properties(jcs_shared PROPERTIES 
    OUTPUT_NAME jcs
    POSITION_INDEPENDENT_CODE ON
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(jcs_shared PUBLIC json-c)

add_library(jcs_static STATIC ${JCS_SOURCES})
set_target_properties(jcs_static PROPERTIES OUTPUT_NAME jcs)
target_link_libraries(jcs_static PUBLIC json-c)

target_include_directories(jcs_shared PUBLIC "src")
target_include_directories(jcs_static PUBLIC "src")

add_executable(test test/main.c)
target_link_libraries(test PUBLIC jcs_static)
