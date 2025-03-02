#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

/*
一个禁止拷贝构造的基类
*/
class Noncopyable
{
public:
    Noncopyable(const Noncopyable &) = delete;
    Noncopyable &operator=(const Noncopyable &) = delete;

protected:
    Noncopyable() = default;
    ~Noncopyable() = default;
};

#endif /* __NONCOPYABLE_H__ */