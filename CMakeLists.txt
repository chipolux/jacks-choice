cmake_minimum_required(VERSION 3.18)

project(jacks-choice)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
    src/main.cpp
)
set(PROJECT_LIBS)
set(PROJECT_INCLUDE_DIRS)

if (APPLE)
    include_directories(SYSTEM /usr/local/include)
endif()

if(${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm")
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
    list(APPEND PROJECT_LIBS pigpio)
    list(APPEND PROJECT_INCLUDE_DIRS ${pigpio_SOURCE_DIR})
endif()

find_library(LIBAO ao REQUIRED)
list(APPEND PROJECT_LIBS ${LIBAO})

find_package(Threads REQUIRED)
list(APPEND PROJECT_LIBS Threads::Threads)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# warn and error for everything
target_compile_options(${PROJECT_NAME} PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror -Wno-comment>
)

if (PROJECT_LIBS)
    target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
endif()
if (PROJECT_INCLUDE_DIRS)
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})
endif()
