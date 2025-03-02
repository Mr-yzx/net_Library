#include "ThreadPool.h"

ThreadPool::ThreadPool(const std::string &name)
        : m_poolName(name), m_isRunning(false)
{

}

ThreadPool::~ThreadPool()
{
    stop();
    for (auto & th : m_threadVec)
    {
        th->join();
    }
}

void ThreadPool::setThreadCallBack(threadFunc &cb_func)
{
    m_func = cb_func;
}

void ThreadPool::setThreadPoolSize(int &num)
{
    m_poolSize = num;
}

void ThreadPool::start()
{
    m_isRunning = true;
    m_threadVec.reserve(m_poolSize);
    for (int i = 0; i < m_poolSize; ++i)
    {
        char id[32] = {0};
        snprintf(id, sizeof(id), "%d", i + 1);
        m_threadVec.emplace_back(new Thread(std::bind(&ThreadPool::runThread, this), m_poolName + id));
        m_threadVec[i]->start();
    }
    if (m_poolSize == 0 && m_func)
    {
        m_func();
    }
}

void ThreadPool::stop()
{
    std::lock_guard<std::mutex> mutex_guard(m_mutex);
    m_isRunning = false;
    m_cond.notify_all();
}

std::string &ThreadPool::getPoolName()
{
    return m_poolName;
}

int ThreadPool::getQueueRealSize()
{
    std::lock_guard<std::mutex> mutex_guard(m_mutex);
    return m_taskQueue.size();
}

void ThreadPool::addTask(threadFunc func)
{
    std::lock_guard<std::mutex> mutex_guard(m_mutex);
    m_taskQueue.push(func);
    m_cond.notify_one();
}


void ThreadPool::runThread()
{
    try
    {
        if (m_func)
        {
            m_func();
        }
        threadFunc task;
        while (true)
        {
            {
                std::unique_lock<std::mutex> lock(m_mutex);
                while (m_taskQueue.empty())
                {
                    if (!m_isRunning)
                    {
                        return;
                    }
                    m_cond.wait(lock);
                }
                task = m_taskQueue.front();
                m_taskQueue.pop();
            }
            if (task)
            {
                task();
            }
        }
    }
    catch(...)
    {
        /*异常日志打印*/
    }
}
