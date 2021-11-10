cmake_minimum_required(VERSION 3.16.0)
if(WIN32)
    #default install path, so no spaces
    set(CMAKE_INSTALL_PREFIX C:/ CACHE PATH "default path" FORCE)
endif()
set(PR_NAME Flappy)
project(${PR_NAME} VERSION 0.1.0)
set (CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

include(CTest)
enable_testing()


find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/SFML/CMakeLists.txt")
    message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()

#---------ADD SOURCE AND HEADER FILES ---------------
set(SOURCE_FILE_NAMES
   Bird 
   Perceptron
   Pipe 
   Player 
   Population 
   Source
)

list(TRANSFORM SOURCE_FILE_NAMES APPEND ".cpp")
list(TRANSFORM SOURCE_FILE_NAMES PREPEND "FlappyBirdAI/")

if(UNIX)
set(CMAKE_INSTALL_RPATH $ORIGIN/../lib)
endif()
add_executable(${PROJECT_NAME} ${SOURCE_FILE_NAMES})

target_include_directories(${PR_NAME}
PRIVATE
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/FlappyBirdAI/>
$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/FlappyBirdAI/>
)

if(WIN32)
    #sfml
 add_custom_command(TARGET ${PR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-audio-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-graphics-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-system-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-window-2.dll"
         ${CMAKE_CURRENT_BINARY_DIR})
endif()

#-----------COPY RES DIR-------------------------
file(COPY fonts DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY images DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")



#---------ADD SFML LIBRARY----------------------------

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/external/SFML")
target_link_libraries(${PR_NAME} sfml-graphics sfml-audio)

#--------INSTALL LINUX---------------------------------
install(TARGETS ${PR_NAME} 
RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_INSTALL_BINDIR})

if(WIN32)
    #sfml
    add_custom_command(TARGET ${PR_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-audio-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-graphics-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-system-2.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/external/SFML/lib/sfml-window-2.dll"
         ${CMAKE_CURRENT_BINARY_DIR})
elseif(UNIX)
    install(TARGETS ${PR_NAME} 
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
endif()

#-------PACKAGING------------------------------------
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack) 
