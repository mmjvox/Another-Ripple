# Another-Ripple
Ripple effect in QML that can be used everywhere

![](https://github.com/mmjvox/Another-Ripple/raw/main/sceencapture.gif)

1. Add .pri to your project  

2. Register qml type in main.cpp or anywhere 
``` 
qmlRegisterType<AnotherRipple>("AnotherRipple", 1, 0, "SimpleRipple"); 
```

3. import in qml 
```
import AnotherRipple 1.0
```

4. Use as an item inside another item:
```
Item{
     width:100
     height:100
      
      SimpleRipple{
          anchors.fill: parent;
          color: "#50ffa070"
      }
}
```

*properties:*

`acceptEvent` 
This is false by default. if you change this to true, it means that Ripple item accepts the click(pressed) events and prevent them to receive to bottom layouts.
`color`
This color of ripple effect.

*methods:*

`pressed(int x , int y)` 
It is used when an item like MouseArea masks Ripple item and doesn't allow clicking(pressing) Ripple item. you can call this and pass mouse x and y to it. 
