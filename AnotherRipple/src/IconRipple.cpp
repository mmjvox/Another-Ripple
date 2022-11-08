#include "IconRipple.h"

namespace AnotherRipple {
IconRipple::IconRipple(QQuickItem *parent) : AnotherRippleBase(parent)
{
}

void IconRipple::paint(QPainter *painter)
{
    if(clipRadius>0 || xClipRadius>0 || yClipRadius>0)
    {
        QPainterPath path;
        path.addRoundedRect(QRectF(0, 0, this->width(), this->height()), xClipRadius>0?xClipRadius:clipRadius , yClipRadius>0?yClipRadius:clipRadius );
//        painter->setClipPath(path);
    }

//    painter->setPen(Qt::NoPen);

    QVectorIterator<std::tuple<qreal,qreal,unsigned int>> i(startPoses);
    int index=0;
    while (i.hasNext()){
        auto pos = i.next();
            double radius= std::get<2>(pos);

            auto newalfa = opacity_calc(radius);

            if(newalfa<0)
            {
                startPoses.remove(index);
                continue;
            }
            else
            {
                painter->setOpacity(newalfa);
            }

            auto transformedImg = mImage.transformed(QMatrix().rotate(rotate_calc(radius)));

            QRectF targetRect(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));
            QRectF sourceRect(0,0, transformedImg.width(), transformedImg.height());
            painter->drawImage(targetRect, transformedImg, sourceRect);


            std::get<2>(pos)=radius+4;
            startPoses.replace(index,pos);
            index++;
    }
    endPaint();
}

void IconRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    tintImage();
    emit colorChanged();
}


QString IconRipple::getImageSource()
{
    return "undefined";
}

void IconRipple::setImageSource(QString source)
{
    if(mImage.load(source))
    {
        auto format = mImage.format();
        if (format != QImage::Format_ARGB32 && format != QImage::Format_ARGB32_Premultiplied)
        {
            format = QImage::Format_ARGB32_Premultiplied;
            mImage = mImage.convertToFormat(format);
        }
        tintImage();
        emit imageSourceChanged();
    }
}

void IconRipple::tintImage()
{
    if(mImage.isNull())
    {
        return;
    }

    QPainter pixmapPainter(&mImage);
    pixmapPainter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
    pixmapPainter.fillRect(mImage.rect(), circleColor);
    pixmapPainter.end();
}

double IconRipple::opacity_calc(double &radius) const
{
    return (1-(radius*0.01));
}
double IconRipple::rotate_calc(double &radius) const
{
    switch (mBounce) {
    case ClockWise:
        return radius;
    case Counter_ClockWise:
        return -radius;
    case None:
    default:
        return 0;
    }
}

int IconRipple::getBounce()
{
    return mBounce;
}

void IconRipple::setBounce(int newBounce)
{
    if(mBounce!=newBounce)
    {
        mBounce=newBounce;
        emit bounceChanged();
    }
}

}
