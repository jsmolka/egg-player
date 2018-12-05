#ifndef READABLEVECTOR_HPP
#define READABLEVECTOR_HPP

#include <QVector>

template <typename T>
class ReadableVector : protected QVector<T>
{
public:
    ReadableVector();
    ReadableVector(const QVector<T> &vector);

    using QVector<T>::at;
    using QVector<T>::first;
    using QVector<T>::last;

    using QVector<T>::size;
    using QVector<T>::isEmpty;
    using QVector<T>::indexOf;

    using QVector<T>::begin;
    using QVector<T>::end;
    using QVector<T>::cbegin;
    using QVector<T>::cend;

    using QVector<T>::operator[];
};

template<typename T>
ReadableVector<T>::ReadableVector()
{

}

template<typename T>
ReadableVector<T>::ReadableVector(const QVector<T> &vector)
    : QVector<T>(vector)
{

}

#endif // READABLEVECTOR_HPP
