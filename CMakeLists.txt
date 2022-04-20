cmake_minimum_required (VERSION 3.0)
project (GumEssentials)

#Set OS
#add_definitions(-DGUM_OS_WINDOWS) 
#add_definitions(-DGUM_OS_BSD)
#add_definitions(-DGUM_OS_MACOS)
add_definitions(-DGUM_OS_LINUX)

add_definitions(-DDEBUG)
#add_definitions(-DCHECK_GL_ERRORS)

set(GUMMATH_DIRECTORY "/home/gumse/Projects/gumball/gum-maths/")

add_subdirectory(./src/)
add_subdirectory(./examples/)
include_directories(${CMAKE_SOURCE_DIR}/external/SFML/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/SFML/src/)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/SFML/)