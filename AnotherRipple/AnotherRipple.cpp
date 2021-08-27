#include "AnotherRipple.h"

AnotherRipple::AnotherRipple(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    this->setAntialiasing(true);
    setAcceptedMouseButtons(Qt::LeftButton);

    timer = new QTimer(this);
    connect(this,&AnotherRipple::stop,timer,&QTimer::stop,Qt::QueuedConnection);
    connect(timer,&QTimer::timeout,this,&AnotherRipple::rePaint,Qt::QueuedConnection);
    timer->setInterval(16);
    timer->start();
}

void AnotherRipple::paint(QPainter *painter)
{
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
    startPoses.append( std::make_tuple(event->localPos().x(),event->localPos().y(), 1) );

    acceptEvent? event->accept() : event->ignore();

    if(!timer->isActive())
        timer->start();
}

void AnotherRipple::pressed(qreal x, qreal y)
{
    startPoses.append( std::make_tuple(x,y, 1) );
    if(!timer->isActive())
        timer->start();
}

void AnotherRipple::rePaint()
{
    this->update();
}

void AnotherRipple::endPaint()
{
    if(startPoses.count()==0)
    {
        //qDebug()<<"this->stop();";
        emit this->stop();
    }
}

qreal AnotherRipple::devide2(qreal pos, int radius)
{
    return pos-radius;
}

qreal AnotherRipple::multipl2(int radius)
{
    return radius*2;
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
