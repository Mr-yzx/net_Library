#ifndef __FIXEDBUFFER_H__
#define __FIXEDBUFFER_H__

#include "Noncopyable.h"

#include <assert.h>
#include <string.h>
#include <strings.h>
#include <string>

#define BUFFER_OF_SMALL 4000
#define BUFFER_OF_LARGE 4000 * 1000

template <int SIZE>
class FixBuffer : Noncopyable
{
public:
    FixBuffer() : m_curData(m_data)
    {

    }

    void append(char *buff, size_t len)
    {
        if (static_cast<size_t>(getAvailable()) > len)
        {
            memcpy(m_curData, buff, len);
            m_curData += len;
        }
    }

    char *getData() { return m_data; }
    int getLength() { return static_cast<int>(end() - m_data); }
    char *getCurData() { return m_curData; }
    int getAvailable() { return static_cast<int>(end() - m_curData); }
    void addData(size_t len) { m_curData += len; }
    void reset() { m_curData = m_data; }
    void bzero() { bzero(m_data, sizeof(m_data)); }

private:
    char *end() { return m_data + sizeof(m_data); }
    char m_data[SIZE];
    char *m_curData;
};

#endif /* __FIXEDBUFFER_H__ */