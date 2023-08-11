cmake_minimum_required(VERSION 3.7)

project(calculate LANGUAGES CXX)

# add definitions
add_definitions(--coverage -fprofile-arcs -ftest-coverage)

# Include diretories
include_directories(/usr/local/include)
link_directories(/usr/local/bin/)

set(CMAKE_C_COMPILER "/usr/local/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_ARCH_TARGET "amd64")

# Set the compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g -Wall -Werror -Wextra --coverage -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/calculate.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

# Создаем цель для генерации отчета о покрытии
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "~/goinfre/homebrew/Cellar/googletest/1.14.0" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "/opt/goinfre/janiecee/homebrew/Cellar/googletest/1.14.0")
endif ()

if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/include)
    set(GMockSrc ${GOOGLETEST_DIR}/include)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message(FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GOOGLETEST_DIR}/include/googletest/googletest/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GOOGLETEST_DIR}/include/googletest/googletest)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GOOGLETEST_DIR}/include/googlemock/googlemock/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GOOGLETEST_DIR}/include/googlemock/googlemock)
endif ()

include_directories(${GTestIncludes})

# Set the sources
set(Sources
                main.cpp
                tstCalculate.cpp
                ../calcModel.cpp
                )

# Set Include directories
include_directories(
                ../
                )

add_executable(calculate ${Sources} ${GTestFiles})

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p gcoverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov --version
    COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp ../calcModel.cpp -o ${OBJECT_DIR}
    COMMAND echo "-- Source diretorie: ${CMAKE_SOURCE_DIR}/"
    COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/gcoverage"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/gcoverage
    )
add_dependencies(gcov calculate)

# Create the lcov target. Run result tests with 'make lcov'
add_custom_target(lcov
    COMMAND mkdir -p lcoverage
    )
add_custom_command(TARGET lcov
    COMMAND echo "=================== LCOV ===================="
    COMMAND echo "-- Passing lcov tool under code coverage"
    COMMAND geninfo --ignore-errors mismatch ${OBJECT_DIR} -b ./lcoverage -o lcoverage/calculate.info
    COMMAND echo "-- Generating HTML output files"
    COMMAND genhtml lcoverage/calculate.info --output-directory lcoverage
    COMMAND open lcoverage/index.html
    )

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES gcoverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(init
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

# Testing
enable_testing()
target_link_libraries(calculate PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
add_test(output_test ${CMAKE_CURRENT_BINARY_DIR}/calculate)
target_link_libraries(calculate PRIVATE Threads::Threads)

# link Boost libraries to the new target
target_link_libraries(calculate PRIVATE gtest)
target_link_libraries(calculate PRIVATE gmock)
target_link_libraries(calculate PRIVATE pthread)
target_link_libraries(calculate PRIVATE -fprofile-arcs)
#target_link_libraries(calculate gcov)
