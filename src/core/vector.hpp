#ifndef GENERICVECTOR_HPP
#define GENERICVECTOR_HPP

#include <QVector>

template <typename T>
class Vector
{
public:
    using iterator = typename QVector<T>::iterator;
    using const_iterator = typename QVector<T>::const_iterator;

    Vector(const QVector<T> &vector);
    virtual ~Vector() = default;

    void setVector(const QVector<T> &vector);
    QVector<T> vector() const;

    T &at(int index);
    const T &at(int index) const;
    const T &first() const;
    const T &last() const;

    bool isEmpty() const;

    int size() const;
    int indexOf(const T &value, int from = 0) const;

    void clear();
    void reserve(int size);

    void insert(int index, const T &value);
    void append(const T &value);
    void remove(int index);

    iterator insert(iterator before, const T &value);
    iterator erase(iterator position);

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    Vector<T> &operator<<(const T &value);
    T &operator[](int index);
    const T &operator[](int index) const;

private:
    QVector<T> m_vector;
};

template <typename T>
inline Vector<T>::Vector(const QVector<T> &vector)
    : m_vector(vector)
{

}

template <typename T>
inline void Vector<T>::setVector(const QVector<T> &vector)
{
    m_vector = vector;
}

template <typename T>
inline QVector<T> Vector<T>::vector() const
{
    return m_vector;
}

template <typename T>
inline T &Vector<T>::at(int index)
{
    return m_vector[index];
}

template <typename T>
inline const T &Vector<T>::at(int index) const
{
    return m_vector.at(index);
}

template <typename T>
inline const T &Vector<T>::first() const
{
    return m_vector.first();
}

template <typename T>
inline const T &Vector<T>::last() const
{
    return m_vector.last();
}

template <typename T>
inline bool Vector<T>::isEmpty() const
{
    return m_vector.isEmpty();
}

template <typename T>
inline int Vector<T>::size() const
{
    return m_vector.size();
}

template <typename T>
inline int Vector<T>::indexOf(const T &value, int from) const
{
    return m_vector.indexOf(value, from);
}

template <typename T>
inline void Vector<T>::clear()
{
    m_vector.clear();
}

template <typename T>
inline void Vector<T>::reserve(int size)
{
    m_vector.reserve(size);
}

template <typename T>
inline void Vector<T>::insert(int index, const T &value)
{
    m_vector.insert(index, value);
}

template <typename T>
inline void Vector<T>::append(const T &value)
{
    m_vector.append(value);
}

template <typename T>
inline void Vector<T>::remove(int index)
{
    m_vector.remove(index);
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::insert(iterator before, const T &value)
{
    return m_vector.insert(before, value);
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::erase(iterator position)
{
    return m_vector.erase(position);
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::begin()
{
    return m_vector.begin();
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::end()
{
    return m_vector.end();
}

template <typename T>
inline typename Vector<T>::const_iterator Vector<T>::cbegin() const
{
    return m_vector.cbegin();
}

template <typename T>
inline typename Vector<T>::const_iterator Vector<T>::cend() const
{
    return m_vector.cend();
}

template <typename T>
inline Vector<T> &Vector<T>::operator<<(const T &value)
{
    m_vector << value;
    return *this;
}

template <typename T>
inline T &Vector<T>::operator[](int index)
{
    return m_vector[index];
}

template <typename T>
inline const T &Vector<T>::operator[](int index) const
{
    return m_vector[index];
}

#endif // GENERICVECTOR_HPP
