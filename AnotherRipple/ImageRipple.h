#ifndef IMAGERIPPLE_H
#define IMAGERIPPLE_H


#include "AnotherRippleBase.h"

namespace AnotherRipple {
class ImageRipple : public AnotherRippleBase
{
    Q_PROPERTY(QString imageSource READ getImageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_OBJECT
public:
    ImageRipple(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;

    void setCircleColor(QString colorSTR) override;

    void setImageSource(QString source);
    QString getImageSource();

signals:
    void imageSourceChanged();

private:
    QImage mImage;
    double opacity_calc(double &radius) const;
    void tintImage();
};
}
#endif // IMAGERIPPLE_H
