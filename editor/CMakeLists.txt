project(editor VERSION 1.0)

if (EMSCRIPTEN)
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")
endif()

find_package(SDL3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(
    editor
    ${SOURCES}
)

if (EMSCRIPTEN)

    target_link_options(
        editor PRIVATE
        -sALLOW_MEMORY_GROWTH
        --preload-file resources/
    )

    target_link_libraries(
        editor PRIVATE
        SDL3::SDL3
        imgui::imgui
        imnodes
    )

    set_target_properties(editor PROPERTIES SUFFIX ".html")

    file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

else()

    target_link_libraries(
        editor PRIVATE
        SDL3::SDL3
        imgui::imgui
        imnodes
    )

    # copy resources
    if (EXISTS ${CMAKE_SOURCE_DIR}/resources)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND 
            ${CMAKE_COMMAND} -E copy_directory 
            ${CMAKE_SOURCE_DIR}/resources
            ${EXECUTABLE_OUTPUT_PATH}/resources
        )
    else()
        message(WARNING "[WARNING] no resource directory!")
    endif()

endif()
