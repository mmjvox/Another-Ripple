#ifndef ICONRIPPLE_H
#define ICONRIPPLE_H


#include "AnotherRippleBase.h"

namespace AnotherRipple {
class IconRipple : public AnotherRippleBase
{
    Q_PROPERTY(QString imageSource READ getImageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(int bounce READ getBounce WRITE setBounce NOTIFY bounceChanged)
    Q_OBJECT
public:
    enum Bounce
    {
        None=-1,
        ClockWise=1,
        Counter_ClockWise
    };
    Q_ENUMS(Bounce)

    IconRipple(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;

    void setCircleColor(QString colorSTR) override;

    void setImageSource(QString source);
    QString getImageSource();

    int getBounce();
    void setBounce(int newBounce);

signals:
    void imageSourceChanged();
    void bounceChanged();

private:
    QImage mImage;
    double rotate_calc(double &radius) const;
    double opacity_calc(double &radius) const;
    void tintImage();
    int mBounce=-1;
};
}
#endif // ICONRIPPLE_H
