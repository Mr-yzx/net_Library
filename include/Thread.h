#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>
#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include "Noncopyable.h"
#include "CurThread.h"

class Thread : Noncopyable
{
public:
    typedef std::function<void()> threadFunc;
    explicit Thread(threadFunc func, const std::string &name = std::string());

    /*开启线程*/
    void start();

    /*等待线程*/
    void join();

    bool isThreadStarted();
    
    /*获取线程ID*/
    pid_t getTheadID();
    std::string getThreadName();

    int getThreadNum();


private:
    void setThreadName();

private:
    bool m_isStart;
    bool m_isJoin;
    pid_t m_threadID;
    std::shared_ptr<std::thread> m_thread;
    threadFunc m_func;
    std::string m_threadName;
    std::atomic<uint32_t> m_threadNum;


};
#endif /* __THREAD_H__ */