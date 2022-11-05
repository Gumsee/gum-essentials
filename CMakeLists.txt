cmake_minimum_required (VERSION 3.0)
project(GumEssentials)
cmake_policy(SET CMP0072 NEW)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

#Set OS
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_definitions(-DGUM_OS_LINUX)
    set(GUM_OS_LINUX true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-DGUM_OS_WINDOWS)
    set(GUM_OS_WINDOWS true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-DGUM_OS_MACOS)
    set(GUM_OS_MACOS true)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    add_definitions(-DGUM_OS_BSD)
    set(GUM_OS_BSD true)
endif()

 
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
