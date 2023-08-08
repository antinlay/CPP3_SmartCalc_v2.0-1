cmake_minimum_required(VERSION 3.5)

project(calculate LANGUAGES CXX)

enable_testing()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Threads REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_ARCH_TARGET "amd64")

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "/opt/goinfre/janiecee/homebrew/Cellar/googletest/1.14.0" STREQUAL "")
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

add_executable(calculate main.cpp tst_calculate.cpp ../calcModel.cpp ${GTestFiles})

target_link_libraries(calculate PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

add_test(NAME calculate COMMAND calculate)
target_link_libraries(calculate PRIVATE Threads::Threads)

# Добавляем покрытие кода с использованием lcov
if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# Создаем цель для генерации отчета о покрытии
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
if (LCOV_PATH AND GENHTML_PATH)
    add_custom_target(coverage
        COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
        COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' --output-file coverage.info
        COMMAND ${LCOV_PATH} --list coverage.info
        COMMAND ${GENHTML_PATH} -o coverage_report coverage.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Generating code coverage report"
    )
endif()

# Добавляем зависимость цели calculate от цели coverage
add_dependencies(calculate coverage)
