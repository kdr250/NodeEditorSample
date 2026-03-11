project(core VERSION 1.0)

if (EMSCRIPTEN)
    set(VCPKG_TARGET_TRIPLET "wasm32-emscripten")
endif()

find_package(Lua REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

if (EMSCRIPTEN)
    add_library(${PROJECT_NAME} STATIC ${SOURCES})
else()
    add_library(${PROJECT_NAME} SHARED ${SOURCES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (EMSCRIPTEN)

    target_link_libraries(
        core PRIVATE
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        core PRIVATE
        ${LUA_INCLUDE_DIR}
    )

else()

    target_link_libraries(
        core PRIVATE
        ${LUA_LIBRARIES}
    )

    target_include_directories(
        core PRIVATE
        ${LUA_INCLUDE_DIR}
    )

endif()
