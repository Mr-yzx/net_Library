#include "TimeStamp.h"

TimeStamp TimeStamp::getTimeNow()
{
    struct timeval timeval;
    gettimeofday(&timeval, nullptr);

    uint64_t senconds = timeval.tv_sec;
    return TimeStamp(senconds * SECONS_TO_MICROSECONDS + timeval.tv_usec);
}

std::string TimeStamp::getTimeToFormatString(bool isShowMicroseconds)
{
    char buff[64] = {0};
    time_t seconds = static_cast<time_t>(m_microSeconds / SECONS_TO_MICROSECONDS);

    struct tm *tmp_time = localtime(&seconds);
    if (isShowMicroseconds)
    {
        uint64_t microSeconds = static_cast<uint64_t>(m_microSeconds % SECONS_TO_MICROSECONDS);
        snprintf(buff, sizeof(buff), "[%04d:%02d:%02d %02d:%02d:%02d.%06d]",
                tmp_time->tm_year + 1900, tmp_time->tm_mon + 1, tmp_time->tm_mday,
                tmp_time->tm_hour, tmp_time->tm_min, tmp_time->tm_sec,
                microSeconds);
    
    }
    else
    {
        snprintf(buff, sizeof(buff), "[%04d:%02d:%02d %02d:%02d:%02d]",
                tmp_time->tm_year + 1900, tmp_time->tm_mon + 1, tmp_time->tm_mday,
                tmp_time->tm_hour, tmp_time->tm_min, tmp_time->tm_sec);
    }
    return std::string(buff);
}
