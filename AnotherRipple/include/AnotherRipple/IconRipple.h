#ifndef ICONRIPPLE_H
#define ICONRIPPLE_H


#include "AnotherRippleBase.h"

namespace AnotherRipple {
class IconRipple : public AnotherRippleBase
{
    Q_PROPERTY(QString imageSource READ getImageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_OBJECT
public:
    IconRipple(QQuickItem *parent = 0);
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
#endif // ICONRIPPLE_H
