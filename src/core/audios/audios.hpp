#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include "core/audios/audiosbase.hpp"
#include "core/audios/audiosstate.hpp"

class Audios : public audios::Base
{
    Q_OBJECT

public:
    using audios::Base::Base;
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
