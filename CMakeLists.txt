cmake_minimum_required(VERSION 3.30)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


project(CubeShooter VERSION 1.0 LANGUAGES C)


find_package(SDL3 REQUIRED CONFIG)

file(GLOB_RECURSE SOURCES src/*.c)
add_executable(CubeShooter ${SOURCES})
target_link_libraries(CubeShooter PRIVATE m SDL3::SDL3)


add_custom_command(TARGET CubeShooter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:CubeShooter>/res
)
