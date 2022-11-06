#ifndef ANOTHERRIPPLEBASE_H
#define ANOTHERRIPPLEBASE_H

#include <QQuickItem>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QPair>
#include <tuple>
#include <QPainterPath>
#include <QVectorIterator>

#include "framehandler.h"

namespace AnotherRipple {
class AnotherRippleBase : public QQuickPaintedItem
{
    Q_PROPERTY(QString color READ getCircleColor WRITE setCircleColor  NOTIFY colorChanged CONSTANT)
    Q_PROPERTY(bool acceptEvent READ getAcceptEvent WRITE setAcceptEvent  NOTIFY acceptEventChanged CONSTANT)
    Q_PROPERTY(int clipRadius WRITE setClipRadius CONSTANT)
    Q_PROPERTY(int xClipRadius WRITE setXClipRadius CONSTANT)
    Q_PROPERTY(int yClipRadius WRITE setYClipRadius CONSTANT)
    Q_OBJECT
public:
    AnotherRippleBase(QQuickItem *parent = 0);
    void mousePressEvent(QMouseEvent *event) override;

    Q_INVOKABLE void pressed(qreal x, qreal y);

    FrameHandler *frameHandler;

    QString getCircleColor();
    virtual void setCircleColor(QString colorSTR);

    bool getAcceptEvent();
    void setAcceptEvent(bool accept);

    void setClipRadius(unsigned int newClipRadius);
    void setXClipRadius(unsigned int newXClipRadius);
    void setYClipRadius(unsigned int newYClipRadius);

signals:
    void stop();
    void colorChanged();
    void acceptEventChanged();

public slots:
    void rePaint();
    void endPaint();

protected:
    unsigned int clipRadius=0,xClipRadius=0,yClipRadius=0;
    QVector<std::tuple<qreal,qreal,unsigned int>> startPoses;
    qreal devide2(qreal, int);
    qreal multipl2(int);
    QColor circleColor="#20000000";
    bool acceptEvent=false;
    bool frameConnected=false;

    void addFrameHandler();
    void removeFrameHandler();
};
}
#endif // ANOTHERRIPPLEBASE_H
