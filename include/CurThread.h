#ifndef __CURTHREAD_H__
#define __CURTHREAD_H__

#include <unistd.h>
#include <sys/syscall.h>

namespace CurThread
{
    extern __thread int m_theadID;
    void getThreadID();

    inline int tid()
    {
        if (__builtin_expect(m_threadID == 0, 0))
        {
            getThreadID();
        }
        return m_threadID;
    }
} // namespace CurThread


#endif /* __CURTHREAD_H__ */