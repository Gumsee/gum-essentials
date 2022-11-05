set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -Wextra -Wno-unused-parameter -Wno-reorder -Wno-pedantic -fdiagnostics-color=always")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") #-Og

message(STATUS "${CMAKE_PROJECT_NAME}: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

#
# Source
#
file(GLOB_RECURSE SRC 
"./*.cpp"

)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC})

include_directories(${CMAKE_SOURCE_DIR}/external/)
include_directories(    ${CMAKE_SOURCE_DIR}/external/libxml2/include)
include_directories(    ${CMAKE_BINARY_DIR}/external/libxml2)
include_directories(    ${CMAKE_SOURCE_DIR}/external/assimp/include)
 
if(OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
endif()
              
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
endif()
              
if(GUMSYSTEM_FOUND)
    include_directories(${GUMSYSTEM_INCLUDE_DIRS})
endif()
              
if(GUMMATHS_FOUND)
    include_directories(${GUMMATHS_INCLUDE_DIRS})
endif()
              
if(DEFINED GUM_OS_BSD)
    if(X11_FOUND)
        include_directories(${X11_INCLUDE_DIRS})
    endif()
endif()
              
if(DEFINED GUM_OS_LINUX)
    if(X11_FOUND)
        include_directories(${X11_INCLUDE_DIRS})
    endif()
endif()
              
if(DEFINED GUM_OS_BSD)
    if(GTK2_FOUND)
        include_directories(${GTK2_INCLUDE_DIRS})
    endif()
endif()
              
if(DEFINED GUM_OS_LINUX)
    if(GTK2_FOUND)
        include_directories(${GTK2_INCLUDE_DIRS})
    endif()
endif()
             

 

install(
    FILES gum-essentials.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/
) 

file(GLOB_RECURSE HEADERS Essentials//*.h)
install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/Essentials//
) 

file(GLOB_RECURSE HEADERS Essentials/Filesystem//*.h)
install(
    FILES ${HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${CMAKE_PROJECT_NAME}/Essentials/Filesystem//
)

install(TARGETS ${CMAKE_PROJECT_NAME}
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake # Not sure if this is still needed
)

configure_package_config_file("Config.cmake.in"
    "${CMAKE_PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
    PATH_VARS CMAKE_INSTALL_LIBDIR
)

#write_basic_package_version_file(
#	${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake
#	VERSION 1.0.0
#	COMPATIBILITY SameMajorVersion
#)

### Install Config and ConfigVersion files
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
#          "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}"
)
