#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QObject>
#include <QVector>

#include "audio.hpp"

using AudioVector = QVector<Audio *>;

class Audios : public QObject
{
    Q_OBJECT

public:
    Audios(QObject *parent = nullptr);
    Audios(const AudioVector &vector, QObject *parent = nullptr);
    ~Audios();

    AudioVector vector() const;

    Audio * at(int index);
    Audio * takeAt(int index);

    AudioVector::iterator begin();
    AudioVector::iterator end();

    AudioVector::const_iterator begin() const;
    AudioVector::const_iterator end() const;

    int size() const;

    bool isEmpty() const;

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);

    Audios & operator<<(Audio *audio);

signals:
    void inserted(int index);
    void removed(int index);
    void updated(Audio *audio);

private:
    AudioVector m_vector;
};

#endif // AUDIOS_HPP
