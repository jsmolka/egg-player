#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include "core/uncopyable.hpp"

template <typename T>
class Singleton : public Uncopyable
{
public:
    static T &instance();
};

template<typename T>
inline T &Singleton<T>::instance()
{
    static T instance;

    return instance;
}

#endif // SINGLETON_HPP
