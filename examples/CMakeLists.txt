set (CMAKE_EXPORT_COMPILE_COMMANDS 1)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS ON)
set (INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}/bin/")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g3 -Wall -Wextra -Wno-pedantic")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0") #Optimization

message(STATUS "Examples: CXXFLAGS: ${CMAKE_CXX_FLAGS}")

#add_compile_options(-pedantic -Wall -Wextra)

find_package(PkgConfig REQUIRED)
find_package(Threads)

include_directories(${CMAKE_SOURCE_DIR}/include/)
include_directories(${CMAKE_SOURCE_DIR}/include/freetype2/)
include_directories(${GUMESSENTIALS_DIRECTORY}/src/)
include_directories(${GUMMATH_DIRECTORY}/src/)
include_directories(${CMAKE_SOURCE_DIR}/src/)
link_directories(${CMAKE_SOURCE_DIR}/lib/)

add_definitions(-DEXAMPLES_PATH=\"${CMAKE_SOURCE_DIR}/examples/\")

set(GUMGUI_LIBRARIES 
    GumEssentials
    GumMaths
    sfml-graphics
    sfml-network
    sfml-audio
    sfml-window
    sfml-system
    GLEW 
    GL
    ${CMAKE_THREAD_LIBS_INIT}
)

set(EXAMPLE_FILE_LIST 
    Window
)


foreach(EXAMPLE ${EXAMPLE_FILE_LIST})
    message(STATUS "Adding target ${EXAMPLE}")
    add_executable(Example_${EXAMPLE} "./${EXAMPLE}.cpp")
    target_link_libraries(Example_${EXAMPLE} ${GUMGUI_LIBRARIES})
endforeach()