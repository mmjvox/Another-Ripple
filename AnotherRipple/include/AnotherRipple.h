#ifndef ANOTHERRIPPLE_H
#define ANOTHERRIPPLE_H

#include "./AnotherRipple/SimpleRipple.h"
#include "./AnotherRipple/ShapedRipple.h"
#include "./AnotherRipple/IconRipple.h"
#include "./AnotherRipple/ImageRipple.h"

namespace AnotherRipple {

    static void init(){
        qmlRegisterType<SimpleRipple>("AnotherRipple", 1, 0, "SimpleRipple");
        qmlRegisterType<ShapedRipple>("AnotherRipple", 1, 0, "ShapedRipple");
        qmlRegisterType<IconRipple>("AnotherRipple", 1, 0, "IconRipple");
        qmlRegisterType<ImageRipple>("AnotherRipple", 1, 0, "ImageRipple");
    }
}

#endif // ANOTHERRIPPLE_H
