#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

/*
时间戳类，用于日志输出显示时间格式
*/

#include <iostream>
#include <string>
#include <sys/time.h>

#define SECONS_TO_MICROSECONDS 1000 * 1000
class TimeStamp
{
public:
    TimeStamp() : m_microSeconds(0)
    {

    }

    explicit TimeStamp(uint64_t microSeconds)
        : m_microSeconds(microSeconds)
    {

    }
    /*获取当前时间戳*/
    static TimeStamp getTimeNow();
    std::string getTimeToString();

    /*返回格式化时间*/
    std::string getTimeToFormatString(bool isShowMicroseconds = false);

    uint64_t getMicroSeconds()
    {
        return m_microSeconds;
    }

    time_t getSeconds()
    {
        return static_cast<time_t>(m_microSeconds / SECONS_TO_MICROSECONDS);
    }

    static TimeStamp invalid()
    {
        return TimeStamp();
    }
    
private:
    uint64_t m_microSeconds;
};

/*
一些运算符的重载
*/

inline bool operator<(TimeStamp ts1, TimeStamp ts2)
{
    return ts1.getMicroSeconds() < ts2.getMicroSeconds();
}

inline bool operator==(TimeStamp ts1, TimeStamp ts2)
{
    return ts1.getMicroSeconds() == ts2.getMicroSeconds();
}

inline TimeStamp addTime(TimeStamp ts, uint64_t seconds)
{
    uint64_t ms = static_cast<uint64_t>(seconds * SECONS_TO_MICROSECONDS);
    return TimeStamp(ts.getMicroSeconds() + ms);
}
#endif /* __TIMESTAMP_H__ */