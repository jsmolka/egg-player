#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QObject>
#include <QVector>

#include "audio.hpp"

class Audios : public QObject
{
    Q_OBJECT

public:
    explicit Audios(QObject *parent = nullptr);
    explicit Audios(const AudioVector &vector, QObject *parent = nullptr);
    ~Audios();

    void setVector(const AudioVector &vector);
    AudioVector vector() const;

    Audio *at(int index);
    Audio *first();
    Audio *last();

    Audio *takeAt(int index);
    Audio *takeFirst();
    Audio *takeLast();

    bool isEmpty() const;

    int size() const;
    int indexOf(Audio *audio) const;

    void clear();
    void reserve(int size);

    void move(int from, int to);
    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);

    AudioVector::iterator insert(AudioVector::iterator before, Audio *audio);
    AudioVector::iterator erase(AudioVector::iterator position);

    AudioVector::iterator begin();
    AudioVector::iterator end();

    AudioVector::reverse_iterator rbegin();
    AudioVector::reverse_iterator rend();

    AudioVector::const_iterator cbegin() const;
    AudioVector::const_iterator cend() const;

    AudioVector::const_reverse_iterator crbegin() const;
    AudioVector::const_reverse_iterator crend() const;

    Audios &operator<<(Audio *audio);

signals:
    void inserted(int index);
    void removed(int index);
    void updated(Audio *audio);

private:
    AudioVector m_vector;
};

#endif // AUDIOS_HPP
