#include "framehandler.h"

namespace AnotherRipple {
FrameHandler* FrameHandler::instance= nullptr;
std::once_flag FrameHandler::initInstanceFlag;


FrameHandler::FrameHandler()
{
    this->start();
    this->setPriority(QThread::LowestPriority);

}

void FrameHandler::run()
{
    while (true) {
        sync.lock();
        if(!running)
            pauseCond.wait(&sync);
        sync.unlock();

        emit onNewFrame();
        this->msleep(1000/fps);
    }
}

void FrameHandler::setFps(unsigned int newFps)
{
    if(newFps>0)
        fps = newFps;
}

void FrameHandler::resume()
{
    sync.lock();
    running = true;
    sync.unlock();
    pauseCond.wakeAll();
}

void FrameHandler::pause()
{
    sync.lock();
    bool anyConnection = this->isSignalConnected(QMetaMethod::fromSignal(&FrameHandler::onNewFrame));
    if(!anyConnection)
        running = false;
    sync.unlock();
}
}
