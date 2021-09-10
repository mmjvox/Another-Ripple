#ifndef ANOTHERRIPPLE_H
#define ANOTHERRIPPLE_H

#include <QQuickItem>
#include <QtQuick/QQuickPaintedItem>
#include <QColor>
#include <QPen>
#include <QPainter>
#include <QPair>
#include <tuple>
#include <QVectorIterator>

#include "rippleframe.h"


class AnotherRipple : public QQuickPaintedItem
{
    Q_PROPERTY(QString color READ getCircleColor WRITE setCircleColor  NOTIFY colorChanged CONSTANT)
    Q_PROPERTY(bool acceptEvent READ getAcceptEvent WRITE setAcceptEvent  NOTIFY acceptEventChanged CONSTANT)
    Q_OBJECT
public:
    AnotherRipple(QQuickItem *parent = 0);
    void paint(QPainter *painter);
    void mousePressEvent(QMouseEvent *event);

    Q_INVOKABLE void pressed(qreal x, qreal y);

    FrameHandler *frameHandler;

    QString getCircleColor();
    void setCircleColor(QString colorSTR);

    bool getAcceptEvent();
    void setAcceptEvent(bool accept);

signals:
    void stop();
    void colorChanged();
    void acceptEventChanged();
    void handleFrames();

public slots:
    void rePaint();
    void endPaint();

private:
    QVector<std::tuple<qreal,qreal,unsigned int>> startPoses;
    qreal devide2(qreal, int);
    qreal multipl2(int);
    QColor circleColor="#20000000";
    bool acceptEvent=false;
    bool frameConnected=false;

    void addFrameHandler();
    void removeFrameHandler();

};

#endif // ANOTHERRIPPLE_H
