#include "ImageRipple.h"

namespace AnotherRipple {
ImageRipple::ImageRipple(QQuickItem *parent) : AnotherRippleBase(parent)
{
}

void ImageRipple::paint(QPainter *painter)
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

            if(newalfa<1)
            {
                painter->setOpacity(newalfa);
            }
            else
            {
                startPoses.remove(index);
                continue;
            }

            QRectF targetRect(devide2(std::get<0>(pos),radius), devide2(std::get<1>(pos),radius), multipl2(radius), multipl2(radius));
            QRectF sourceRect(0,0, mImage.width(), mImage.height());
            painter->drawImage(targetRect, mImage, sourceRect);


            std::get<2>(pos)=radius+4;
            startPoses.replace(index,pos);
            index++;
    }
    endPaint();
}

void ImageRipple::setCircleColor(QString colorSTR)
{
    circleColor = colorSTR;
    tintImage();
    emit colorChanged();
}


QString ImageRipple::getImageSource()
{
    return "undefined";
}

void ImageRipple::setImageSource(QString source)
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

void ImageRipple::tintImage()
{
    if(mImage.isNull())
    {
        return;
    }

    QImage baseLayer(mImage.size(), QImage::Format_ARGB32_Premultiplied);
    baseLayer.fill(circleColor);

    QPainter layerPainter(&baseLayer);
    QRectF sourceRect(mImage.rect());

//    QImage maskLayer = mImage.createAlphaMask();
//    maskLayer.setAlphaChannel(mImage.alphaChannel());
//    layerPainter.drawImage(sourceRect,maskLayer);

    layerPainter.setOpacity(0.9);
    layerPainter.drawImage(sourceRect,mImage);
    layerPainter.end();
    mImage = baseLayer;
}

double ImageRipple::opacity_calc(double &radius) const
{
    return radius*0.01;
}
}
