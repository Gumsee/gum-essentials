#
# Source
#
file(GLOB_RECURSE SRC 
"./*.cpp"

)
add_library(${CMAKE_PROJECT_NAME} STATIC ${SRC})

include_directories(${CMAKE_SOURCE_DIR}/external/)

 
        if(GUMMATHS_FOUND)
            include_directories(${GUMMATHS_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GUMMATHS cannot not found)
        endif() 
        if(GUMSYSTEM_FOUND)
            include_directories(${GUMSYSTEM_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GUMSYSTEM cannot not found)
        endif() 
        if(DEFINED GUM_OS_BSD)
        if(X11_FOUND)
            include_directories(${X11_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for X11 cannot not found)
        endif() 
    endif() 
        if(DEFINED GUM_OS_LINUX)
        if(X11_FOUND)
            include_directories(${X11_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for X11 cannot not found)
        endif() 
    endif() 
        if(DEFINED GUM_OS_BSD)
        if(GTK2_FOUND)
            include_directories(${GTK2_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GTK2 cannot not found)
        endif() 
    endif() 
        if(DEFINED GUM_OS_LINUX)
        if(GTK2_FOUND)
            include_directories(${GTK2_INCLUDE_DIRS})
        else()
            message(FATAL_ERROR Library for GTK2 cannot not found)
        endif() 
    endif() 
    include_directories(${CMAKE_SOURCE_DIR}/external/libxml2/include) 
    include_directories(${CMAKE_BINARY_DIR}/external/libxml2) 
    include_directories(${CMAKE_SOURCE_DIR}/external/assimp/include)

 

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
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(
    EXPORT ${CMAKE_PROJECT_NAME}Targets
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}
    FILE ${CMAKE_PROJECT_NAME}Targets.cmake
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

export(PACKAGE ${CMAKE_PROJECT_NAME})

