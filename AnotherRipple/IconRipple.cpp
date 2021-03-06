#include "IconRipple.h"

IconRipple::IconRipple(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    frameHandler  = FrameHandler::getInstance();
}

void IconRipple::paint(QPainter *painter)
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
            int radius= std::get<2>(pos);

            int decColor=100+(radius/4);

            if(decColor>150)
            {
                startPoses.remove(index);
                continue;
            }

            auto color=circleColor.lighter(decColor);
            painter->setBrush(QBrush(color,Qt::SolidPattern));


            QGraphicsColorizeEffect *effect = new QGraphicsColorizeEffect();
                effect->setColor(Qt::red);
            QGraphicsSvgItem *svg = new QGraphicsSvgItem(QString("/oldhome/mmjvox/Downloads/energy.svg"));
                 svg->setGraphicsEffect(effect);

                 svg->setZValue(100);
                 svg->setRotation(45);
                 svg->setVisible(false);

            svg->renderer()->render(painter,QRectF(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius)));

//            painter->drawRect(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));

            std::get<2>(pos)=radius+4;
            startPoses.replace(index,pos);
            index++;
    }
    endPaint();
}

void IconRipple::mousePressEvent(QMouseEvent *event)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();
}

void IconRipple::pressed(qreal x, qreal y)
{
    addFrameHandler();

    startPoses.append( std::make_tuple(x,y, 1) );
}

void IconRipple::rePaint()
{
    this->update();
}

void IconRipple::endPaint()
{
    if(startPoses.count()==0)
    {
        removeFrameHandler();
        emit this->stop();
    }
}

void IconRipple::setYClipRadius(unsigned int newYClipRadius)
{
    if(newYClipRadius>=0)
        yClipRadius = newYClipRadius;
}

void IconRipple::setXClipRadius(unsigned int newXClipRadius)
{
    if(newXClipRadius>=0)
        xClipRadius = newXClipRadius;
}

void IconRipple::setClipRadius(unsigned int newClipRadius)
{
    if(newClipRadius>=0)
        clipRadius = newClipRadius;
}

qreal IconRipple::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal IconRipple::multipl2(int radius)
{
    return radius*2;
}

void IconRipple::removeFrameHandler()
{
    if(frameConnected){
        frameConnected= !disconnect(frameHandler,&FrameHandler::onNewFrame,this,&IconRipple::rePaint);
        frameHandler->pause();
    }
}

void IconRipple::addFrameHandler()
{
    if(!frameConnected)
    {
        frameConnected = connect(frameHandler,&FrameHandler::onNewFrame,this,&IconRipple::rePaint,Qt::QueuedConnection);
        frameHandler->resume();
    }

}

QString IconRipple::getCircleColor()
{
    return circleColor.name();
}

void IconRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    emit colorChanged();
}

bool IconRipple::getAcceptEvent()
{
    return acceptEvent;
}

void IconRipple::setAcceptEvent(bool accept)
{
    acceptEvent=accept;
    emit acceptEventChanged();
}
