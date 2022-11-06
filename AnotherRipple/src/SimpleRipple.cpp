#include "SimpleRipple.h"

namespace AnotherRipple {
SimpleRipple::SimpleRipple(QQuickItem *parent) : AnotherRippleBase(parent)
{
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
}
