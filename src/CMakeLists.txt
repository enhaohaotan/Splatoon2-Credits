
set(libraries glad glfw)

file(GLOB_RECURSE target_inc "*.h" )
file(GLOB_RECURSE target_src "*.cpp" )

add_executable(${PROJECT_NAME} ${target_inc} ${target_src})
target_link_libraries(${PROJECT_NAME} ${libraries})
