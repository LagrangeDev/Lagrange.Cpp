cmake_minimum_required(VERSION 3.12)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Lagrange.OneBot)
set(CMAKE_CXX_STANDARD 26)

if(MSVC)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/dist")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/dist")

include_directories("${CMAKE_SOURCE_DIR}/Largange.Common/include")
include_directories("${CMAKE_SOURCE_DIR}/Lagrange.Core/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
# file(GLOB HEADERS "${CMAKE_SOURCE_DIR}/Largange.Common/include/**/*.h")
file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp")
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_executable(
    Lagrange.OneBot "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp"
    ${SOURCES}
    ${HEADERS}
    "${CMAKE_SOURCE_DIR}/Largange.Common/assets/Lagrange.OneBot.exe.manifest"
  )
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_executable(Lagrange.OneBot  "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp" ${SOURCES} ${HEADERS})
endif()
