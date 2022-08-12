set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -Wextra -Wno-unused-parameter -Wno-reorder -Wno-pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") #-Og

message(STATUS "GumEssentials: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

#add_compile_options(${CMAKE_CXX_FLAGS})

#
# Directories
#
include_directories(${CMAKE_SOURCE_DIR}/external/libxml2/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/SFML/include/)
include_directories(${CMAKE_SOURCE_DIR}/external/glfw/include/)
include_directories(${CMAKE_BINARY_DIR}/external/libxml2/)
include_directories(${GUMMATH_DIRECTORY})

#
# Source
#
file(GLOB_RECURSE SRC "./*.cpp")

add_library(GumEssentials STATIC ${SRC})


file(GLOB HEADERS "./Essentials/*.h")
install(
	FILES ${HEADERS} 
	DESTINATION ${GUM_INSTALLDIR}/Essentials/
)

file(GLOB HEADERS "./Essentials/Input/*.h")
install(
	FILES ${HEADERS} 
	DESTINATION ${GUM_INSTALLDIR}/Essentials/Input/
)

file(GLOB HEADERS "./Essentials/Filesystem/*.h")
install(
	FILES ${HEADERS} 
	DESTINATION ${GUM_INSTALLDIR}/Essentials/Filesystem/
)

install(
	FILES "./gum-essentials.h"
	DESTINATION ${GUM_INSTALLDIR}/
)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
