QT += quick gui svg

CONFIG += c++11

SOURCES += \
        $$PWD/src/AnotherRippleBase.cpp \
        $$PWD/src/ShapedRipple.cpp \
        $$PWD/src/SimpleRipple.cpp \
        $$PWD/src/IconRipple.cpp \
        $$PWD/src/ImageRipple.cpp \
        $$PWD/src/framehandler.cpp

HEADERS += \
    $$PWD/include/AnotherRipple/AnotherRippleBase.h \
    $$PWD/include/AnotherRipple/ShapedRipple.h \
    $$PWD/include/AnotherRipple/SimpleRipple.h \
    $$PWD/include/AnotherRipple/IconRipple.h \
    $$PWD/include/AnotherRipple/ImageRipple.h \
    $$PWD/include/AnotherRipple/framehandler.h \
    $$PWD/include/AnotherRipple.h

INCLUDEPATH += $$PWD/include/AnotherRipple
INCLUDEPATH += $$PWD/include
