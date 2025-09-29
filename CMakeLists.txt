cmake_minimum_required(VERSION 3.20)
project(IXRay_Agent LANGUAGES C CXX)

# CXX options
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Настройка путей
set(LUA_SRC_DIR ${CMAKE_SOURCE_DIR}/lua-5.1/src)
set(LUA_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lua-5.1/src)

# Файлы Lua 5.1
set(LUA_CORE_SOURCES
    ${LUA_SRC_DIR}/lapi.c ${LUA_SRC_DIR}/lcode.c ${LUA_SRC_DIR}/ldebug.c
    ${LUA_SRC_DIR}/ldo.c ${LUA_SRC_DIR}/ldump.c ${LUA_SRC_DIR}/lfunc.c
    ${LUA_SRC_DIR}/lgc.c ${LUA_SRC_DIR}/llex.c ${LUA_SRC_DIR}/lmem.c
    ${LUA_SRC_DIR}/lobject.c ${LUA_SRC_DIR}/lopcodes.c ${LUA_SRC_DIR}/lparser.c
    ${LUA_SRC_DIR}/lstate.c ${LUA_SRC_DIR}/lstring.c ${LUA_SRC_DIR}/ltable.c
    ${LUA_SRC_DIR}/ltm.c ${LUA_SRC_DIR}/lundump.c ${LUA_SRC_DIR}/lvm.c
    ${LUA_SRC_DIR}/lzio.c
)

set(LUA_LIB_SOURCES
    ${LUA_SRC_DIR}/lauxlib.c ${LUA_SRC_DIR}/lbaselib.c ${LUA_SRC_DIR}/ldblib.c
    ${LUA_SRC_DIR}/liolib.c ${LUA_SRC_DIR}/lmathlib.c ${LUA_SRC_DIR}/loslib.c
    ${LUA_SRC_DIR}/lstrlib.c ${LUA_SRC_DIR}/ltablib.c ${LUA_SRC_DIR}/loadlib.c
    ${LUA_SRC_DIR}/linit.c
)

# Создание статической библиотеки Lua
add_library(lua51 STATIC ${LUA_CORE_SOURCES} ${LUA_LIB_SOURCES})
target_compile_definitions(lua51 PRIVATE LUA_USE_LINUX)
target_include_directories(lua51 PUBLIC ${LUA_INCLUDE_DIR})

# Ваша Lua-библиотека на C++23
add_library(xr_agent SHARED xr_agent.cpp)
target_include_directories(xr_agent PUBLIC ${CMAKE_SOURCE_DIR} ${LUA_INCLUDE_DIR})
target_link_libraries(xr_agent PRIVATE lua51)

# Установка свойств для shared library
set_target_properties(xr_agent PROPERTIES
    VERSION 1.0
    SOVERSION 1
    OUTPUT_NAME "xr_agent"
    PREFIX ""
)

# Установка флагов компиляции
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(xr_agent PRIVATE -Wall -Wextra -fPIC)
endif()