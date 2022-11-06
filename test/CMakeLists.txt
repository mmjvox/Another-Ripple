cmake_minimum_required(VERSION 3.1)

project(MyRippleTest LANGUAGES CXX)
set(PACKAGE_NAME Test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(Qt5 COMPONENTS Core Quick Gui REQUIRED)


include_directories(
  ../AnotherRipple/include
)

if(ANDROID)
    add_library(MyRippleTest SHARED main.cpp qml.qrc)
else()
    add_executable(MyRippleTest main.cpp qml.qrc)
endif()

target_compile_definitions(MyRippleTest
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(MyRippleTest
    PRIVATE Qt5::Core Qt5::Quick Qt5::Gui AnotherRipple)


