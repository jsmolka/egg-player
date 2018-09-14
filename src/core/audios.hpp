#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QObject>

#include "audio.hpp"
#include "genericvector.hpp"

class Audios : public QObject, public GenericVector<Audio *>
{
    Q_OBJECT

public:
    using iterator = GenericVector::iterator;
    using const_iterator = GenericVector::const_iterator;

    explicit Audios(QObject *parent = nullptr);
    explicit Audios(const Audio::vector &vector, QObject *parent = nullptr);

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);
    void remove(Audio *audio);

    iterator insert(iterator before, Audio *audio);
    iterator erase(iterator position);

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
