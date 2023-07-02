cmake_minimum_required(VERSION 3.21)

if(NOT DEFINED IC_VERSION_MACRO)
  set(IC_VERSION_MACRO 0)
endif()

if(NOT DEFINED IC_VERSION_MAJOR)
  set(IC_VERSION_MAJOR 0)
endif()

if(NOT DEFINED IC_VERSION_MINOR)
  set(IC_VERSION_MINOR 1)
endif()

if(NOT DEFINED IC_VERSION_PATCH)
  set(IC_VERSION_PATCH 0)
endif()

if(NOT DEFINED IC_VERSION_BRANCH)
  set(IC_VERSION_BRANCH master)
endif()

if(NOT DEFINED IC_VERSION_STATUS)
  set(IC_VERSION_STATUS Dev)
endif()

if (NOT PACKAGE_VERSION)
  set(PACKAGE_VERSION
    "${IC_VERSION_MACRO}.${IC_VERSION_MAJOR}.${IC_VERSION_MINOR}.${IC_VERSION_PATCH}.${IC_VERSION_BRANCH}.${IC_VERSION_STATUS}")
endif()


project(ic
  VERSION ${IC_VERSION_MACRO}.${IC_VERSION_MAJOR}.${IC_VERSION_MINOR}.${IC_VERSION_PATCH}
  LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS YES)

include_directories(${CMAKE_SOURCE_DIR}/MiF/ibasicLibrary/include)
include_directories(${CMAKE_SOURCE_DIR}/third-party)

link_directories(${CMAKE_SOURCE_DIR}/MiF/ibasicLibrary/lib)

file(
        GLOB_RECURSE SRC_FILES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/include/*.hpp
        ${PROJECT_SOURCE_DIR}/include/iLexer/*.h
        ${PROJECT_SOURCE_DIR}/include/iLexer/*.hpp
        ${PROJECT_SOURCE_DIR}/include/iLexer/*.inl
        ${PROJECT_SOURCE_DIR}/include/iParse/*.h
        ${PROJECT_SOURCE_DIR}/include/iParse/*.hpp
        ${PROJECT_SOURCE_DIR}/include/iParse/*.inl
        ${PROJECT_SOURCE_DIR}/include/iAST/*.h
        ${PROJECT_SOURCE_DIR}/include/iAST/*.hpp
        ${PROJECT_SOURCE_DIR}/include/iAST/*.inl
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.rc
        ${PROJECT_SOURCE_DIR}/src/iLexer/*.cpp
        ${PROJECT_SOURCE_DIR}/src/iLexer/*.hpp
        ${PROJECT_SOURCE_DIR}/src/iLexer/*.h
        ${PROJECT_SOURCE_DIR}/src/iParse/*.cpp
        ${PROJECT_SOURCE_DIR}/src/iParse/*.hpp
        ${PROJECT_SOURCE_DIR}/src/iParse/*.h
        ${PROJECT_SOURCE_DIR}/src/iAST/*.cpp
        ${PROJECT_SOURCE_DIR}/src/iAST/*.hpp
        ${PROJECT_SOURCE_DIR}/src/iAST/*.h
)

# third-party source files
file(GLOB_RECURSE THIRD_PARTY_SRC_FILES ${CMAKE_SOURCE_DIR}/third-party/rawpdb/*)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")


add_executable(ic ${SRC_FILES} ${THIRD_PARTY_SRC_FILES})

target_link_libraries(ic I:/root/ai/Feilulu/WorkArea/Programming/MiracleForest/ic/MiF/lib/iBasicLibrary_debug.lib)

target_compile_options(
        ic
        PRIVATE /experimental:module /diagnostics:column /source-charset:utf-8 /execution-charset:GBK 
)

target_compile_definitions(
        ic
        PRIVATE _CONSOLE _UNICODE UNICODE
)

