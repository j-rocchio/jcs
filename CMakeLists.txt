cmake_minimum_required(VERSION 3.25)
project(jcs LANGUAGES C VERSION 0.0.0)
set(CMAKE_C_STANDARD 99)

# build json-c, set compiler options, and collect sorces
add_subdirectory(json-c EXCLUDE_FROM_ALL SYSTEM)
add_compile_options(-Wall -Wextra -Wpedantic)
file(GLOB JCS_SOURCES "src/*.c")

# build shared library
add_library(jcs_shared SHARED ${JCS_SOURCES})
set_target_properties(jcs_shared PROPERTIES 
    OUTPUT_NAME jcs
    POSITION_INDEPENDENT_CODE ON
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})
target_link_libraries(jcs_shared PUBLIC json-c)
target_include_directories(jcs_shared PUBLIC "src")

# build static library
add_library(jcs_static STATIC ${JCS_SOURCES})
set_target_properties(jcs_static PROPERTIES OUTPUT_NAME jcs)
target_link_libraries(jcs_static PUBLIC json-c)
target_include_directories(jcs_static PUBLIC "src")

# build code gen executable
add_executable(jcs_gen gen/main.c)
target_link_libraries(jcs_gen PUBLIC jcs_static)

# build test executable
add_executable(test test/main.c)
target_link_libraries(test PUBLIC jcs_static)
