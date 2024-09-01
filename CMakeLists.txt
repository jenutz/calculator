cmake_minimum_required(VERSION 3.14)

project(calculator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Test REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/icons)
set(PROJECT_SOURCES
       ${PROJECT_SOURCE_DIR}/src/Main.cpp
       ${PROJECT_SOURCE_DIR}/src/Calculator.h
       ${PROJECT_SOURCE_DIR}/src/Calculator.cpp
       ${PROJECT_SOURCE_DIR}/src/qml.qrc
       ${PROJECT_SOURCE_DIR}/icons/icons.qrc
)


qt_add_executable(calculator
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(calculator
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set(TESTS
       tests/test_backend.cpp 
       src/Calculator.cpp
)

qt_add_executable(test_backend
    MANUAL_FINALIZATION
    ${TESTS}
)
target_link_libraries(test_backend
    PRIVATE Qt6::Test Qt6::Core Qt6::Quick)
enable_testing()
add_test(NAME BackendTests COMMAND test_backend)
