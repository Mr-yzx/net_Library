#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <queue>
#include <vector>
#include <mutex>
#include <condition_variable>

#include "Noncopyable.h"
#include "Thread.h"

class ThreadPool : Noncopyable
{
public:
    typedef std::function<void()> threadFunc;
    ThreadPool(const std::string &name = std::string("Threadpool"));
    ~ThreadPool();

    void setThreadCallBack(threadFunc &cb_func);

    void setThreadPoolSize(int &num);
    void start();
    void stop();
    
    std::string &getPoolName();

    int getQueueRealSize();
    void addTask(threadFunc func);

private:
    void runThread();

private:
    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::string m_poolName;
    std::vector<std::unique_ptr<Thread>> m_threadVec;
    std::queue<threadFunc> m_taskQueue;
    threadFunc m_func;
    bool m_isRunning;
    int m_poolSize;
};

#endif /* __THREADPOOL_H__ */