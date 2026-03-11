project(viewer VERSION 1.0)

if (EMSCRIPTEN)
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")
endif()

find_package(Lua REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(
    viewer
    ${SOURCES}
)

target_link_libraries(
    viewer PRIVATE
    core
)

if (EMSCRIPTEN)

    target_link_options(
        viewer PRIVATE
        -sASYNCIFY
        -sEXPORTED_RUNTIME_METHODS=['ccall']
        -lidbfs.js
        -sFORCE_FILESYSTEM
        --profiling-funcs
        -sALLOW_MEMORY_GROWTH
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
