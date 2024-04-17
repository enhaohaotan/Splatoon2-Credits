# ---------------------------------------------------------------------------------
# Projects Settings
# ---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()

# ---------------------------------------------------------------------------------
# Cmake projects
# ---------------------------------------------------------------------------------
project(Splatoon2_Credits)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

#set(LIBRARIES_SOURCE_PATH ${PROJECT_SOURCE_DIR}/libraries)

include_directories(
    ${PROJECT_SOURCE_DIR}/libraries/glad/include
    ${PROJECT_SOURCE_DIR}/libraries/glfw/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/libraries)
add_subdirectory(${PROJECT_SOURCE_DIR}/src)

#add_executable(${PROJECT_NAME} src/main.cpp)
#target_link_libraries(${PROJECT_NAME} glfw)
