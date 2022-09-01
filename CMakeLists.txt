cmake_minimum_required (VERSION 3.0)
project (GumEssentials)

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



#add_definitions(-DDEBUG)
#add_definitions(-DCHECK_GL_ERRORS)

set(GUM_INSTALLDIR "/usr/include/gumball/")
set(GUMBALL_INCLUDE_DIR "/usr/include/gumball/")
set(GUMMATH_DIRECTORY ${GUMBALL_INCLUDE_DIR})


#
# Building external libs
#
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glfw/)


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
add_subdirectory(${CMAKE_SOURCE_DIR}/external/libxml2/)

add_subdirectory(./src/)
add_subdirectory(./examples/)
