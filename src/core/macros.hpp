#ifndef MACROS_HPP
#define MACROS_HPP

#define EGG_MEMBER(type, var)               \
    type m_##var;                           \

#define EGG_CSETTER(type, var, set)         \
    inline void set(const type &var)        \
    {                                       \
        m_##var = var;                      \
    }                                       \

#define EGG_PSETTER(type, var, set)         \
    inline void set(type var)               \
    {                                       \
        m_##var = var;                      \
    }                                       \

#define EGG_GETTER(type, var, get)          \
    inline type get() const                 \
    {                                       \
        return m_##var;                     \
    }                                       \

#define EGG_CPROP(type, var, set, get)      \
    private:                                \
        EGG_MEMBER(type, var)               \
    public:                                 \
        EGG_CSETTER(type, var, set)         \
        EGG_GETTER(type, var, get)          \

#define EGG_PPROP(type, var, set, get)      \
    private:                                \
        EGG_MEMBER(type, var)               \
    public:                                 \
        EGG_PSETTER(type, var, set)         \
        EGG_GETTER(type, var, get)          \

#endif // MACROS_HPP
