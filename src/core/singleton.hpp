#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "core/uncopyable.hpp"

template <typename T>
class Singleton : private Uncopyable
{
public:
    static T &instance();
};

template<typename T>
inline T &Singleton<T>::instance()
{
    static T t;

    return t;
}

#endif // SINGLETON_HPP
