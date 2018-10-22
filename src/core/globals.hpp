#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#define CPROP(var, type, set, get)      \
    private:                            \
        type m_##var;                   \
    public:                             \
        void ##set(const ##type &##var) \
        {                               \
            m_##var = ##var;            \
        }                               \
        type ##get() const              \
        {                               \
            return m_##var;             \
        }                               \

#define PPROP(var, type, set, get)      \
    private:                            \
        type m_##var;                   \
    public:                             \
        void ##set(##type ##var)        \
        {                               \
            m_##var = ##var;            \
        }                               \
        type ##get() const              \
        {                               \
            return m_##var;             \
        }                               \

#endif // GLOBALS_HPP
