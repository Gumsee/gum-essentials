set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -fdiagnostics-color=always")
if(DEFINED GUM_OS_LINUX)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra -Wno-unused-parameter -Wno-reorder -Wno-pedantic")
elseif(DEFINED GUM_OS_WINDOWS)

endif()
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") #Optimization

message(STATUS "Examples: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

list(APPEND GUM_LIBRARIES ${CMAKE_PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

 
if(GUMSYSTEM_FOUND)
    list(APPEND GUM_LIBRARIES "${GUMSYSTEM_LIBRARIES}")
else()
    message(FATAL_ERROR Library for GUMSYSTEM cannot not found)
endif()
              
if(GUMMATHS_FOUND)
    list(APPEND GUM_LIBRARIES "${GUMMATHS_LIBRARIES}")
else()
    message(FATAL_ERROR Library for GUMMATHS cannot not found)
endif()
              
if(DEFINED GUM_OS_BSD)
    if(X11_FOUND)
        list(APPEND GUM_LIBRARIES "${X11_LIBRARIES}")
    else()
        message(FATAL_ERROR Library for X11 cannot not found)
    endif()
endif()
              
if(DEFINED GUM_OS_LINUX)
    if(X11_FOUND)
        list(APPEND GUM_LIBRARIES "${X11_LIBRARIES}")
    else()
        message(FATAL_ERROR Library for X11 cannot not found)
    endif()
endif()
              
if(DEFINED GUM_OS_BSD)
    if(GTK2_FOUND)
        list(APPEND GUM_LIBRARIES "${GTK2_LIBRARIES}")
    else()
        message(FATAL_ERROR Library for GTK2 cannot not found)
    endif()
endif()
              
if(DEFINED GUM_OS_LINUX)
    if(GTK2_FOUND)
        list(APPEND GUM_LIBRARIES "${GTK2_LIBRARIES}")
    else()
        message(FATAL_ERROR Library for GTK2 cannot not found)
    endif()
endif()
             

include_directories(${CMAKE_SOURCE_DIR}/src/)
 
if(GUMSYSTEM_FOUND)
    include_directories(${GUMSYSTEM_INCLUDE_DIRS})
else()
    message(FATAL_ERROR Library for GUMSYSTEM cannot not found)
endif()
              
if(GUMMATHS_FOUND)
    include_directories(${GUMMATHS_INCLUDE_DIRS})
else()
    message(FATAL_ERROR Library for GUMMATHS cannot not found)
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
             

link_directories(${CMAKE_BINARY_DIR}/src/)

add_definitions(-DEXAMPLES_PATH=\"${CMAKE_SOURCE_DIR}/examples\")

set(EXAMPLE_FILE_LIST ImageToHeaderConverter)

foreach(EXAMPLE ${EXAMPLE_FILE_LIST})
    message(STATUS "Adding target ${EXAMPLE}")
    add_executable(Example_${EXAMPLE} "./${EXAMPLE}.cpp")
    target_link_libraries(Example_${EXAMPLE} "${GUM_LIBRARIES}")
endforeach()
