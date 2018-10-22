#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define EGG_MEMBER(type, var)           \
    private:                            \
        type m_##var;                   \

#define EGG_GETTER(type, var, get)      \
    public:                             \
        type get() const                \
        {                               \
            return m_##var;             \
        }                               \

#define EGG_CSETTER(type, var, set)     \
    public:                             \
        void set(const type &var)       \
        {                               \
            m_##var = var;              \
        }                               \

#define EGG_PSETTER(type, var, set)     \
    public:                             \
        void set(type var)              \
        {                               \
            m_##var = var;              \
        }                               \

#define EGG_CPROP(type, var, set, get)  \
    EGG_MEMBER(type, var)               \
    EGG_CSETTER(type, var, set)         \
    EGG_GETTER(type, var, get)          \

#define EGG_PPROP(type, var, set, get)  \
    EGG_MEMBER(type, var)               \
    EGG_PSETTER(type, var, set)         \
    EGG_GETTER(type, var, get)          \

#endif // GLOBALS_HPP
