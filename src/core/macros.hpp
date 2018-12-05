#ifndef MACROS_HPP
#define MACROS_HPP

#define EGG_MEMBER(type, var)                \
    type m_##var;                            \

#define EGG_C_SETTER(type, var, set)         \
    inline void set(const type &var)         \
    {                                        \
        m_##var = var;                       \
    }                                        \

#define EGG_P_SETTER(type, var, set)         \
    inline void set(type var)                \
    {                                        \
        m_##var = var;                       \
    }                                        \

#define EGG_GETTER(type, var, get)           \
    inline type get() const                  \
    {                                        \
        return m_##var;                      \
    }                                        \

#define EGG_C_PROP(type, var, set, get)      \
    private:                                 \
        EGG_MEMBER(type, var)                \
    public:                                  \
        EGG_C_SETTER(type, var, set)         \
        EGG_GETTER(type, var, get)           \

#define EGG_P_PROP(type, var, set, get)      \
    private:                                 \
        EGG_MEMBER(type, var)                \
    public:                                  \
        EGG_P_SETTER(type, var, set)         \
        EGG_GETTER(type, var, get)           \

#define EGG_REF_CAST(cls, type, func)        \
    const_cast<type &>(                      \
        static_cast<const cls &>(            \
            *this).func())                   \

#define EGG_PPROP EGG_P_PROP
#define EGG_CPROP EGG_C_PROP

#endif // MACROS_HPP
