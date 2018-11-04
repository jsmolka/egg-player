#ifndef UNCOPYABLE_HPP
#define UNCOPYABLE_HPP

class Uncopyable
{
public:
    Uncopyable(const Uncopyable &) = delete;
    Uncopyable &operator=(const Uncopyable &) = delete;

protected:
    Uncopyable() = default;
    ~Uncopyable() = default;
};

#endif // UNCOPYABLE_HPP
