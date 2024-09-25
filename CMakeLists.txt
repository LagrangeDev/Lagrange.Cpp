cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lagrange.Cpp")
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

# 区分构建模式
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-D DEBUG)
endif()
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-D RELEASE)
endif()

# 区分平台

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_definitions(-D _WIN_PLATFORM_)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_definitions(-D _LINUX_PLATFORM_)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_definitions(-D _DARWIN_PLATFORM_)
endif()
add_subdirectory("Lagrange.Core")
add_subdirectory("Lagrange.OneBot")
