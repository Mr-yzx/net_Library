#include "CurThread.h"

namespace CurThread
{
    __thread int m_threadID = 0;
    
    void getThreadID()
    {
        if (m_threadID == 0)
        {
            m_threadID = static_cast<pid_t>(syscall(SYS_gettid));
        }
    }
} // namespace name

