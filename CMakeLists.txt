cmake_minimum_required (VERSION 3.0)
project(GumEssentials)
cmake_policy(SET CMP0072 NEW)
cmake_policy(SET CMP0090 NEW)
set(CMAKE_EXPORT_PACKAGE_REGISTRY TRUE)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

#Set OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DGUM_OS_LINUX)
    set(GUM_OS_LINUX true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DGUM_OS_WINDOWS)
    set(GUM_OS_WINDOWS true)

    set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Gumlib/")

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DGUM_OS_MACOS)
    set(GUM_OS_MACOS true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    add_definitions(-DGUM_OS_BSD)
    set(GUM_OS_BSD true)
endif()

set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")
if(DEFINED GUM_OS_LINUX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -fdiagnostics-color=always")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wno-unused-parameter -Wno-reorder -Wno-pedantic")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") #-Og
elseif(DEFINED GUM_OS_WINDOWS)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Wall")
endif()

set(CMAKE_INSTALL_FULL_INCLUDEDIR /)
set(CMAKE_INSTALL_FULL_LIBDIR /)

message(STATUS "${CMAKE_PROJECT_NAME}: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

 
find_package(OpenGL REQUIRED)
              
find_package(GLEW REQUIRED)
              
find_package(GumSystem REQUIRED)
              
find_package(GumMaths REQUIRED)
              
if(DEFINED GUM_OS_BSD)
	find_package(X11 REQUIRED)
endif()
              
if(DEFINED GUM_OS_LINUX)
	find_package(X11 REQUIRED)
endif()
              
if(DEFINED GUM_OS_BSD)
	find_package(GTK2 REQUIRED)
endif()
              
if(DEFINED GUM_OS_LINUX)
	find_package(GTK2 REQUIRED)
endif()
             

#add_definitions(-DDEBUG)
add_definitions(-DCHECK_GL_ERRORS)

#
# Building external libs
#
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(LIBXML2_WITH_C14N "Add the Canonicalization support" OFF)
option(LIBXML2_WITH_CATALOG "Add the Catalog support" OFF)
option(LIBXML2_WITH_DEBUG "Add the debugging module" OFF)
option(LIBXML2_WITH_FTP "Add the FTP support" OFF)
option(LIBXML2_WITH_HTML "Add the HTML support" OFF)
option(LIBXML2_WITH_HTTP "Add the HTTP support" OFF)
option(LIBXML2_WITH_ICONV "Add ICONV support" OFF)
option(LIBXML2_WITH_ICU "Add ICU support" OFF)
option(LIBXML2_WITH_ISO8859X "Add ISO8859X support if no iconv" OFF)
option(LIBXML2_WITH_LEGACY "Add deprecated APIs for compatibility" OFF)
option(LIBXML2_WITH_LZMA "Use liblzma" OFF)
option(LIBXML2_WITH_MEM_DEBUG "Add the memory debugging module" OFF)
option(LIBXML2_WITH_MODULES "Add the dynamic modules support" OFF)
option(LIBXML2_WITH_OUTPUT "Add the serialization support" ON)
option(LIBXML2_WITH_PATTERN "Add the xmlPattern selection interface" OFF)
option(LIBXML2_WITH_PROGRAMS "Build programs" OFF)
option(LIBXML2_WITH_PUSH "Add the PUSH parser interfaces" OFF)
option(LIBXML2_WITH_PYTHON "Build Python bindings" OFF)
option(LIBXML2_WITH_READER "Add the xmlReader parsing interface" ON)
option(LIBXML2_WITH_REGEXPS "Add Regular Expressions support" OFF)
option(LIBXML2_WITH_RUN_DEBUG "Add the runtime debugging module" OFF)
option(LIBXML2_WITH_SAX1 "Add the older SAX1 interface" OFF)
option(LIBXML2_WITH_SCHEMAS "Add Relax-NG and Schemas support" OFF)
option(LIBXML2_WITH_SCHEMATRON "Add Schematron support" OFF)
option(LIBXML2_WITH_TESTS "Build tests" OFF)
option(LIBXML2_WITH_THREADS "Add multithread support" ON)
option(LIBXML2_WITH_THREAD_ALLOC "Add per-thread memory" OFF)
option(LIBXML2_WITH_TREE "Add the DOM like tree manipulation APIs" OFF)
option(LIBXML2_WITH_VALID "Add the DTD validation support" OFF)
option(LIBXML2_WITH_WRITER "Add the xmlWriter saving interface" ON)
option(LIBXML2_WITH_XINCLUDE "Add the XInclude support" OFF)
option(LIBXML2_WITH_XPATH "Add the XPATH support" OFF)
option(LIBXML2_WITH_XPTR "Add the XPointer support" OFF)
option(LIBXML2_WITH_ZLIB "Use libz" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/external/libxml2/ EXCLUDE_FROM_ALL)

#option(ASSIMP_BUILD_TESTS "" OFF)
set(ASSIMP_BUILD_TESTS OFF CACHE INTERNAL "")
add_subdirectory(${CMAKE_SOURCE_DIR}/external/assimp/ EXCLUDE_FROM_ALL)

add_subdirectory(src)
add_subdirectory(examples)
