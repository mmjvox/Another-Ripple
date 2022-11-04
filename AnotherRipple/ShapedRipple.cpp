#include "ShapedRipple.h"

ShapedRipple::ShapedRipple(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    frameHandler  = FrameHandler::getInstance();
}

void ShapedRipple::paint(QPainter *painter)
{
    if(clipRadius>0 || xClipRadius>0 || yClipRadius>0)
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
        double radius= std::get<2>(pos);

        auto newalfa = alfa_calc(radius);
        auto newColor = circleColor;

        if(newalfa>=0)
        {
            newColor.setAlpha(newalfa);
        }
        else
        {
            startPoses.remove(index);
            continue;
        }

        painter->setBrush(QBrush(newColor,Qt::SolidPattern));
        painter->drawRect(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));

        std::get<2>(pos)=radius+4;
        startPoses.replace(index,pos);
        index++;
    }
    endPaint();
}

void ShapedRipple::mousePressEvent(QMouseEvent *event)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();
}

void ShapedRipple::pressed(qreal x, qreal y)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(x,y, 1) );
}

void ShapedRipple::rePaint()
{
    this->update();
}

void ShapedRipple::endPaint()
{
    if(startPoses.count()==0)
    {
        removeFrameHandler();
        emit this->stop();
    }
}

void ShapedRipple::setYClipRadius(unsigned int newYClipRadius)
{
    if(newYClipRadius>=0)
        yClipRadius = newYClipRadius;
}

void ShapedRipple::setXClipRadius(unsigned int newXClipRadius)
{
    if(newXClipRadius>=0)
        xClipRadius = newXClipRadius;
}

void ShapedRipple::setClipRadius(unsigned int newClipRadius)
{
    if(newClipRadius>=0)
        clipRadius = newClipRadius;
}

qreal ShapedRipple::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal ShapedRipple::multipl2(int radius)
{
    return radius*2;
}

void ShapedRipple::removeFrameHandler()
{
    if(frameConnected){
        frameConnected= !disconnect(frameHandler,&FrameHandler::onNewFrame,this,&ShapedRipple::rePaint);
        frameHandler->pause();
    }
}

void ShapedRipple::addFrameHandler()
{
    if(!frameConnected)
    {
        frameConnected = connect(frameHandler,&FrameHandler::onNewFrame,this,&ShapedRipple::rePaint,Qt::QueuedConnection);
        frameHandler->resume();
    }

}

QString ShapedRipple::getCircleColor()
{
    return circleColor.name();
}

void ShapedRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    emit colorChanged();
}

bool ShapedRipple::getAcceptEvent()
{
    return acceptEvent;
}

void ShapedRipple::setAcceptEvent(bool accept)
{
    acceptEvent=accept;
    emit acceptEventChanged();
}

double ShapedRipple::alfa_calc(double &radius) const
{
    double circleColorAlpha = circleColor.alpha();
    if(circleColorAlpha>0){

        double mAlfaDivision = mAlfaRatio / circleColorAlpha;

        if(mAlfaDivision>0){

            double decColor = radius / mAlfaDivision;
            return circleColor.alpha()-decColor;
        }
        return 0;
    }
    return 0;
}
