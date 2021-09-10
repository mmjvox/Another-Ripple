#include "AnotherRipple.h"

AnotherRipple::AnotherRipple(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    frameHandler  = FrameHandler::getInstance();
}

void AnotherRipple::paint(QPainter *painter)
{
    if(clipRadius>0 or xClipRadius>0 or yClipRadius>0)
    {
        QPainterPath path;
        path.addRoundedRect(QRectF(0, 0, this->width(), this->height()), xClipRadius>0?xClipRadius:clipRadius , yClipRadius>0?yClipRadius:clipRadius );
        painter->setClipPath(path);
    }

    painter->setPen(Qt::NoPen);

    QVectorIterator<std::tuple<qreal,qreal,unsigned int>> i(startPoses);
    int index=0;
    while (i.hasNext()){
        auto pos = i.next();
            int radius= std::get<2>(pos);

            int decColor=100+(radius/4);

            if(decColor>150)
            {
                startPoses.remove(index);
                continue;
            }

            auto color=circleColor.lighter(decColor);
            painter->setBrush(QBrush(color,Qt::SolidPattern));

            painter->drawEllipse(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));

            std::get<2>(pos)=radius+4;
            startPoses.replace(index,pos);
            index++;
    }
    endPaint();
}

void AnotherRipple::mousePressEvent(QMouseEvent *event)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();
}

void AnotherRipple::pressed(qreal x, qreal y)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(x,y, 1) );
}

void AnotherRipple::rePaint()
{
    this->update();
}

void AnotherRipple::endPaint()
{
    if(startPoses.count()==0)
    {
        removeFrameHandler();
        emit this->stop();
    }
}

void AnotherRipple::setYClipRadius(unsigned int newYClipRadius)
{
    if(newYClipRadius>=0)
        yClipRadius = newYClipRadius;
}

void AnotherRipple::setXClipRadius(unsigned int newXClipRadius)
{
    if(newXClipRadius>=0)
        xClipRadius = newXClipRadius;
}

void AnotherRipple::setClipRadius(unsigned int newClipRadius)
{
    if(newClipRadius>=0)
        clipRadius = newClipRadius;
}

qreal AnotherRipple::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal AnotherRipple::multipl2(int radius)
{
    return radius*2;
}

void AnotherRipple::removeFrameHandler()
{
    if(frameConnected){
        frameConnected= !disconnect(frameHandler,&FrameHandler::onNewFrame,this,&AnotherRipple::rePaint);
        frameHandler->pause();
    }
}

void AnotherRipple::addFrameHandler()
{
    if(!frameConnected)
    {
        frameConnected = connect(frameHandler,&FrameHandler::onNewFrame,this,&AnotherRipple::rePaint,Qt::QueuedConnection);
        frameHandler->resume();
    }

}

QString AnotherRipple::getCircleColor()
{
    return circleColor.name();
}

void AnotherRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    emit colorChanged();
}

bool AnotherRipple::getAcceptEvent()
{
    return acceptEvent;
}

void AnotherRipple::setAcceptEvent(bool accept)
{
    acceptEvent=accept;
    emit acceptEventChanged();
}
