project(viewer VERSION 1.0)

if (EMSCRIPTEN)
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")
endif()

find_package(Lua REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(
    viewer
    ${SOURCES}
)

if (EMSCRIPTEN)

    target_link_options(
        viewer PRIVATE
        -sALLOW_MEMORY_GROWTH
        --preload-file resources/
    )

    target_link_libraries(
        viewer PRIVATE
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        viewer PRIVATE
        ${LUA_INCLUDE_DIR}
    )

    set_target_properties(viewer PROPERTIES SUFFIX ".html")

else()

    target_link_libraries(
        viewer PRIVATE
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        viewer PRIVATE
        ${LUA_INCLUDE_DIR}
    )

endif()
