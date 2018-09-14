#ifndef GENERICVECTOR_HPP
#define GENERICVECTOR_HPP

#include <QVector>

template <typename T>
class GenericVector
{
public:
    using iterator = typename QVector<T>::iterator;
    using const_iterator = typename QVector<T>::const_iterator;

    GenericVector(const QVector<T> &vector);

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

    void move(int from, int to);
    void insert(int index, const T &value);
    void append(const T &value);
    void remove(int index);

    iterator insert(iterator before, const T &value);
    iterator erase(iterator position);

    iterator begin();
    iterator end();

    const_iterator cbegin() const;
    const_iterator cend() const;

    GenericVector<T> &operator<<(const T &value);

private:
    QVector<T> m_vector;
};

template <typename T>
inline GenericVector<T>::GenericVector(const QVector<T> &vector)
    : m_vector(vector)
{

}

template <typename T>
inline void GenericVector<T>::setVector(const QVector<T> &vector)
{
    m_vector = vector;
}

template <typename T>
inline QVector<T> GenericVector<T>::vector() const
{
    return m_vector;
}

template <typename T>
inline T &GenericVector<T>::at(int index)
{
    return m_vector[index];
}

template <typename T>
inline const T &GenericVector<T>::at(int index) const
{
    return m_vector.at(index);
}

template <typename T>
inline const T &GenericVector<T>::first() const
{
    return m_vector.first();
}

template <typename T>
inline const T &GenericVector<T>::last() const
{
    return m_vector.last();
}

template <typename T>
inline bool GenericVector<T>::isEmpty() const
{
    return m_vector.isEmpty();
}

template <typename T>
inline int GenericVector<T>::size() const
{
    return m_vector.size();
}

template <typename T>
inline int GenericVector<T>::indexOf(const T &value, int from) const
{
    return m_vector.indexOf(value, from);
}

template <typename T>
inline void GenericVector<T>::clear()
{
    m_vector.clear();
}

template <typename T>
inline void GenericVector<T>::reserve(int size)
{
    m_vector.reserve(size);
}

template <typename T>
inline void GenericVector<T>::move(int from, int to)
{
    m_vector.move(from, to);
}

template <typename T>
inline void GenericVector<T>::insert(int index, const T &value)
{
    m_vector.insert(index, value);
}

template <typename T>
inline void GenericVector<T>::append(const T &value)
{
    m_vector.append(value);
}

template <typename T>
inline void GenericVector<T>::remove(int index)
{
    m_vector.remove(index);
}

template <typename T>
inline typename GenericVector<T>::iterator GenericVector<T>::insert(iterator before, const T &value)
{
    return m_vector.insert(before, value);
}

template <typename T>
inline typename GenericVector<T>::iterator GenericVector<T>::erase(iterator position)
{
    return m_vector.erase(position);
}

template <typename T>
inline typename GenericVector<T>::iterator GenericVector<T>::begin()
{
    return m_vector.begin();
}

template <typename T>
inline typename GenericVector<T>::iterator GenericVector<T>::end()
{
    return m_vector.end();
}

template <typename T>
inline typename GenericVector<T>::const_iterator GenericVector<T>::cbegin() const
{
    return m_vector.cbegin();
}

template <typename T>
inline typename GenericVector<T>::const_iterator GenericVector<T>::cend() const
{
    return m_vector.cend();
}

template <typename T>
inline GenericVector<T> &GenericVector<T>::operator<<(const T &value)
{
    m_vector << value;
    return *this;
}

#endif // GENERICVECTOR_HPP
