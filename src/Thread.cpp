#include "Thread.h"
#include <semaphore.h>

Thread::Thread(threadFunc func, const std::string &name)
        : m_isStart(false), m_isJoin(false), m_threadID(0),
          m_func(std::move(func)), m_threadName(name)
{

}

Thread::~Thread()
{
    if (m_isStart && !m_isJoin)
    {
        m_thread->detach();
    }
}
void Thread::start()
{
    m_isStart = true;
    sem_t sem;
    /*
    信号量初始化，第二个参数设置为 false 表示在线程间共享
    */
    sem_init(&sem, false, 0);

    /*开启一个线程*/

    m_thread = std::shared_ptr<std::thread>(new std::thread([&](){
        /*这里需要获取子线程id,通过信号量唤醒主线程*/
        m_threadID = CurThread::tid();
        sem_post(&sem);
        /*子线程执行功能函数*/
        m_func();

    }));
    /*此处主线程阻塞，等待子线程获取到id之后,主线程才能继续执行*/
    sem_wait(&sem);

}

void Thread::join()
{
    m_isJoin = true;
    m_thread->join();
}

bool Thread::isThreadStarted()
{
    return m_isStart;
}

pid_t Thread::getTheadID()
{
    return m_threadID;
}

std::string Thread::getThreadName()
{
    return m_threadName;
}

int Thread::getThreadNum()
{
    return m_threadNum;
}

void Thread::setThreadName()
{
    int num = ++m_threadNum;
    if (m_threadName.empty())
    {
        char buff[32] = {0};
        snprintf(buff, sizeof(buff), "thread%d", num);
        m_threadName = std::string(buff);
    }
}
