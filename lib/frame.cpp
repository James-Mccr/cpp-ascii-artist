#include "frame.h"
#include <chrono>
#include <thread>

Frame::Frame(long _fps) 
{
    milliseconds_per_frame = (1000 / _fps);
}

void Frame::limit()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_per_frame));
}