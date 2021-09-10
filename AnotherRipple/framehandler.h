#ifndef FRAMEHANDLER_H
#define FRAMEHANDLER_H

#include <QObject>
#include <QMetaMethod>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QDebug>

class FrameHandler : public QThread
{
    Q_OBJECT
public:
    static FrameHandler * getInstance()
    {
      std::call_once(initInstanceFlag, &FrameHandler::initSingleton);

      return instance;
    }

    void run() override;


    void setFps(unsigned int newFps);

    void resume();
    void pause();

public slots:
    void handleFrames();

signals:
    void onNewFrame();


private:
    FrameHandler();
    static FrameHandler    *instance;
    static std::once_flag  initInstanceFlag;
    static void  initSingleton()
    {
      instance = new FrameHandler;
    }

    unsigned int fps = 60;

    QMutex sync;
    QWaitCondition pauseCond;
    bool running=false;
};

#endif // FRAMEHANDLER_H
