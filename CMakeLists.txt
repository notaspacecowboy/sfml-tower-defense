cmake_minimum_required(VERSION 3.16)
project(game)

set(CMAKE_CXX_STANDARD 17)

file(GLOB source_files
        "src/*.cpp"
        "src/Core/*.cpp"
        "src/Data/*.cpp"
        "src/Input/*.cpp"
        "src/Components/*.cpp"
        "src/Resource/*.cpp"
        "src/States/*.cpp"
        "src/Utils/*.cpp"
        "src/Renderer/*.cpp"
        "src/Audio/*.cpp"
        "src/Prefabs/*.cpp"
        "src/Grid/*.cpp"
)

set(SOURCES ${source_files})

# detect and add SFML as static library
find_package(SFML COMPONENTS graphics network audio window system REQUIRED)
if (NOT SFML_FOUND)
    message(FATAL_ERROR "SFML NOT FOUND!")
else()
    message("SFML Found!")
endif()

find_package(LDtkLoader)

include_directories("./include")
add_executable(${PROJECT_NAME} ${SOURCES} )
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)
target_link_libraries(${PROJECT_NAME} PRIVATE LDtkLoader)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        ${CMAKE_CURRENT_BINARY_DIR}/data)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets)


# enable make install command
install(TARGETS ${PROJECT_NAME}	RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/install)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_SOURCE_DIR}/install)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_SOURCE_DIR}/install)
