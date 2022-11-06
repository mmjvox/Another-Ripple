#ifndef SIMPLERIPPLE_H
#define SIMPLERIPPLE_H


#include "AnotherRippleBase.h"

namespace AnotherRipple {
class SimpleRipple : public AnotherRippleBase
{
public:
    SimpleRipple(QQuickItem *parent = 0);
    void paint(QPainter *painter) override;


private:
    const double mAlfaRatio = 128;
    double alfa_calc(double &radius) const;

};
}
#endif // SIMPLERIPPLE_H
