project(core VERSION 1.0)

if (EMSCRIPTEN)
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")
endif()

find_package(Lua REQUIRED)
find_package(imgui CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_library(core STATIC ${SOURCES} ${HEADERS})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (EMSCRIPTEN)

    target_link_libraries(
        core PRIVATE
        imgui::imgui
        imnodes
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        core PRIVATE
        ${LUA_INCLUDE_DIR}
    )

else()

    target_link_libraries(
        core PRIVATE
        imgui::imgui
        imnodes
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        core PRIVATE
        ${LUA_INCLUDE_DIR}
    )

endif()
