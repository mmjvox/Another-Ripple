#include "AnotherRippleBase.h"

namespace AnotherRipple {
AnotherRippleBase::AnotherRippleBase(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    frameHandler  = FrameHandler::getInstance();
}

void AnotherRippleBase::mousePressEvent(QMouseEvent *event)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();
}

void AnotherRippleBase::pressed(qreal x, qreal y)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(x,y, 1) );
}

void AnotherRippleBase::rePaint()
{
    this->update();
}

void AnotherRippleBase::endPaint()
{
    if(startPoses.count()==0)
    {
        removeFrameHandler();
        emit this->stop();
    }
}

void AnotherRippleBase::setYClipRadius(unsigned int newYClipRadius)
{
    if(newYClipRadius>=0)
    {
        yClipRadius = newYClipRadius;
    }
}

void AnotherRippleBase::setXClipRadius(unsigned int newXClipRadius)
{
    if(newXClipRadius>=0)
    {
        xClipRadius = newXClipRadius;
    }
}

void AnotherRippleBase::setClipRadius(unsigned int newClipRadius)
{
    if(newClipRadius>=0)
    {
        clipRadius = newClipRadius;
    }
}

qreal AnotherRippleBase::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal AnotherRippleBase::multipl2(int radius)
{
    return radius*2;
}

void AnotherRippleBase::removeFrameHandler()
{
    if(frameConnected){
        frameConnected= !disconnect(frameHandler,&FrameHandler::onNewFrame,this,&AnotherRippleBase::rePaint);
        frameHandler->pause();
    }
}

void AnotherRippleBase::addFrameHandler()
{
    if(!frameConnected)
    {
        frameConnected = connect(frameHandler,&FrameHandler::onNewFrame,this,&AnotherRippleBase::rePaint,Qt::QueuedConnection);
        frameHandler->resume();
    }

}

QString AnotherRippleBase::getCircleColor()
{
    return circleColor.name();
}

void AnotherRippleBase::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    emit colorChanged();
}

bool AnotherRippleBase::getAcceptEvent()
{
    return acceptEvent;
}

void AnotherRippleBase::setAcceptEvent(bool accept)
{
    acceptEvent=accept;
    emit acceptEventChanged();
}
}
