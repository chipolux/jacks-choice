cmake_minimum_required(VERSION 3.18)
project(jacks-choice)

find_package(pigpio QUIET)
if (NOT pigpio_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        pigpio
        GIT_REPOSITORY https://github.com/joan2937/pigpio.git
        GIT_TAG v79
    )
    FetchContent_MakeAvailable(pigpio)
endif()

find_library(LIBAO ao REQUIRED)

set(PROJECT_SOURCES
    src/main.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
target_link_libraries(${PROJECT_NAME} pigpio ${LIBAO})
target_include_directories(${PROJECT_NAME} PRIVATE ${pigpio_SOURCE_DIR})
