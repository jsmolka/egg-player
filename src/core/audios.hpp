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
    explicit Audios(const Audio::vector &vector, QObject *parent = nullptr);
    ~Audios();

    void setVector(const Audio::vector &vector);
    Audio::vector vector() const;

    Audio *at(int index);
    Audio *first();
    Audio *last();

    bool isEmpty() const;

    int size() const;
    int indexOf(Audio *audio) const;

    void clear();
    void reserve(int size);

    void move(int from, int to);
    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);
    void remove(Audio *audio);

    Audio::vector::iterator insert(Audio::vector::iterator before, Audio *audio);
    Audio::vector::iterator erase(Audio::vector::iterator position);

    Audio::vector::iterator begin();
    Audio::vector::iterator end();

    Audio::vector::const_iterator cbegin() const;
    Audio::vector::const_iterator cend() const;

    Audios &operator<<(Audio *audio);

private slots:
    void onAudioUpdated(Audio *audio);

signals:
    void inserted(int index);
    void removed(int index);
    void updated(int index);

private:
    Audio::vector m_vector;
};

#endif // AUDIOS_HPP
