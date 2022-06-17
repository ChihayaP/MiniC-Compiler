cmake_minimum_required(VERSION 3.21)

project(${PROJECT_NAME} C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_BUILD_TOOL "Debug")

set(PROJECT_NAME main)

add_executable(${PROJECT_NAME}
    parser.tab.c
    parser.tab.h
    lex.yy.c
    main.c
    ast.c
    ast.h
)

add_custom_command(OUTPUT
    lex.yy.c
    PRE_BUILD
    COMMAND
    flex -o lex.yy.c ../lex.l
    DEPENDS
    lex.l
)

add_custom_command(OUTPUT
    parser.tab.c parser.tab.h
    PRE_BUILD
    COMMAND
    bison -d -o parser.tab.c ../parser.y
    DEPENDS
    parser.y
)

find_package(PkgConfig REQUIRED)
IF(PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
    PKG_CHECK_MODULES(LIBGVC libgvc)
ENDIF()

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBGVC_INCLUDE_DIRS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${LIBGVC_DEFINITIONS})
target_link_libraries(${PROJECT_NAME}  PRIVATE ${LIBGVC_LIBRARIES})
target_link_directories(${PROJECT_NAME} PRIVATE ${LIBGVC_LIBRARY_DIRS})