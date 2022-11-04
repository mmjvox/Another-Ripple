#include "SimpleRipple.h"

SimpleRipple::SimpleRipple(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    frameHandler  = FrameHandler::getInstance();
}

void SimpleRipple::paint(QPainter *painter)
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
        painter->drawEllipse(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));

        std::get<2>(pos)=radius+4;
        startPoses.replace(index,pos);
        index++;
    }
    endPaint();
}

void SimpleRipple::mousePressEvent(QMouseEvent *event)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();
}

void SimpleRipple::pressed(qreal x, qreal y)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(x,y, 1) );
}

void SimpleRipple::rePaint()
{
    this->update();
}

void SimpleRipple::endPaint()
{
    if(startPoses.count()==0)
    {
        removeFrameHandler();
        emit this->stop();
    }
}

void SimpleRipple::setYClipRadius(unsigned int newYClipRadius)
{
    if(newYClipRadius>=0)
        yClipRadius = newYClipRadius;
}

void SimpleRipple::setXClipRadius(unsigned int newXClipRadius)
{
    if(newXClipRadius>=0)
        xClipRadius = newXClipRadius;
}

void SimpleRipple::setClipRadius(unsigned int newClipRadius)
{
    if(newClipRadius>=0)
        clipRadius = newClipRadius;
}

qreal SimpleRipple::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal SimpleRipple::multipl2(int radius)
{
    return radius*2;
}

void SimpleRipple::removeFrameHandler()
{
    if(frameConnected){
        frameConnected= !disconnect(frameHandler,&FrameHandler::onNewFrame,this,&SimpleRipple::rePaint);
        frameHandler->pause();
    }
}

void SimpleRipple::addFrameHandler()
{
    if(!frameConnected)
    {
        frameConnected = connect(frameHandler,&FrameHandler::onNewFrame,this,&SimpleRipple::rePaint,Qt::QueuedConnection);
        frameHandler->resume();
    }

}

QString SimpleRipple::getCircleColor()
{
    return circleColor.name();
}

void SimpleRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    emit colorChanged();
}

bool SimpleRipple::getAcceptEvent()
{
    return acceptEvent;
}

void SimpleRipple::setAcceptEvent(bool accept)
{
    acceptEvent=accept;
    emit acceptEventChanged();
}

double SimpleRipple::alfa_calc(double &radius) const
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
