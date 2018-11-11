#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include "core/audios/staticvector.hpp"
#include "core/audios/state.hpp"

class Audios : public audios::StaticVector
{
    Q_OBJECT

public:
    using audios::StaticVector::StaticVector;
    ~Audios();

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);

    Audios::iterator insert(Audios::iterator before, Audio *audio);
    Audios::iterator erase(Audios::iterator position);

    int lowerBound(Audio *audio);

    audios::State *currentState();

    Audios &operator<<(Audio *audio);

public slots:
    void removeAudio(Audio *audio);

signals:
    void inserted(int index);
    void updated(int index);
};

#endif // AUDIOS_HPP
