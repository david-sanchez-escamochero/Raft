#pragma once

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <string>
#include "Tracer.h"
using namespace std;


class Semaphore {
public:
    Semaphore(int count_ = 0)
        : count(count_)
    {
    }

    inline void notify(int tid) {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        //Log::trace("thread " + std::to_string(tid) + " notify\r\n");        
        //notify the waiting thread
        cv.notify_one();
    }
    inline void wait(int tid) {
        std::unique_lock<std::mutex> lock(mtx);
        while (count == 0) {            
            //wait on the mutex until notify is called
            cv.wait(lock);            
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};
