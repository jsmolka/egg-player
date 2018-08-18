#ifndef BIMAP_HPP
#define BIMAP_HPP

#include <QHash>

template <typename T1, typename T2>
class Bimap
{
public:
    void insert(const T1 &value1, const T2 &value2);
    void insert(const T2 &value2, const T1 &value1);

    void remove(const T1 &key);
    void remove(const T2 &key);

    T2 value(const T1 &key) const;
    T1 value(const T2 &key) const;

    bool contains(const T1 &key) const;
    bool contains(const T2 &key) const;

    void reserve(int size);

    bool isEmpty() const;

    typename QHash<T1, T2>::iterator begin();
    typename QHash<T1, T2>::iterator end();

    typename QHash<T1, T2>::const_iterator cbegin() const;
    typename QHash<T1, T2>::const_iterator cend() const;

private:
    QHash<T1, T2> m_hash;
    QHash<T2, T1> m_reverse;
};

template <typename T1, typename T2>
inline void Bimap<T1, T2>::insert(const T1 &value1, const T2 &value2)
{
    m_hash.insert(value1, value2);
    m_reverse.insert(value2, value1);
}

template <typename T1, typename T2>
inline void Bimap<T1, T2>::insert(const T2 &value2, const T1 &value1)
{
    insert(value1, value2);
}

template <typename T1, typename T2>
inline void Bimap<T1, T2>::remove(const T1 &key)
{
    m_reverse.remove(m_hash.value(key));
    m_hash.remove(key);
}

template <typename T1, typename T2>
inline void Bimap<T1, T2>::remove(const T2 &key)
{
    m_hash.remove(m_reverse.value(key));
    m_reverse.remove(key);
}

template <typename T1, typename T2>
inline T2 Bimap<T1, T2>::value(const T1 &key) const
{
    return m_hash.value(key);
}

template <typename T1, typename T2>
inline T1 Bimap<T1, T2>::value(const T2 &key) const
{
    return m_reverse.value(key);
}

template <typename T1, typename T2>
inline bool Bimap<T1, T2>::contains(const T1 &key) const
{
    return m_hash.contains(key);
}

template <typename T1, typename T2>
inline bool Bimap<T1, T2>::contains(const T2 &key) const
{
    return m_reverse.contains(key);
}

template <typename T1, typename T2>
inline void Bimap<T1, T2>::reserve(int size)
{
    m_hash.reserve(size);
    m_reverse.reserve(size);
}

template <typename T1, typename T2>
inline bool Bimap<T1, T2>::isEmpty() const
{
    return m_hash.isEmpty();
}

template <typename T1, typename T2>
inline typename QHash<T1, T2>::iterator Bimap<T1, T2>::begin()
{
    return m_hash.begin();
}

template <typename T1, typename T2>
inline typename QHash<T1, T2>::iterator Bimap<T1, T2>::end()
{
    return m_hash.end();
}

template <typename T1, typename T2>
inline typename QHash<T1, T2>::const_iterator Bimap<T1, T2>::cbegin() const
{
    return m_hash.cbegin();
}

template <typename T1, typename T2>
inline typename QHash<T1, T2>::const_iterator Bimap<T1, T2>::cend() const
{
    return m_hash.cend();
}

#endif // BIMAP_HPP
