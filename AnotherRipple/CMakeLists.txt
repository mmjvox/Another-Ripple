cmake_minimum_required(VERSION 3.1)

project(LibAnotherRipple LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick Gui REQUIRED)

include_directories(
  include
  include/AnotherRipple
)

add_library(AnotherRipple STATIC

  include/AnotherRipple.h

  include/AnotherRipple/framehandler.h
  include/AnotherRipple/AnotherRippleBase.h
  include/AnotherRipple/IconRipple.h
  include/AnotherRipple/ImageRipple.h
  include/AnotherRipple/ShapedRipple.h
  include/AnotherRipple/SimpleRipple.h


  src/framehandler.cpp
  src/AnotherRippleBase.cpp
  src/IconRipple.cpp
  src/ImageRipple.cpp
  src/ShapedRipple.cpp
  src/SimpleRipple.cpp
)


target_link_libraries(AnotherRipple PRIVATE Qt5::Core Qt5::Quick Qt5::Gui)

target_compile_definitions(AnotherRipple PRIVATE AnotherRipple_LIBRARY)
