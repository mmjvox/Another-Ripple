#ifndef SHAPEDRIPPLE_H
#define SHAPEDRIPPLE_H


#include "AnotherRippleBase.h"

namespace AnotherRipple {
class ShapedRipple : public AnotherRippleBase
{
public:
    ShapedRipple(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;


private:
    const double mAlfaRatio = 128;
    double alfa_calc(double &radius) const;

};
}
#endif // SHAPEDRIPPLE_H
