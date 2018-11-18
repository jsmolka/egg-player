#ifndef AUDIOS_HPP
#define AUDIOS_HPP

#include <QSet>

#include "core/audios/frozenvector.hpp"
#include "core/audios/currentstate.hpp"

class Audios : public audios::FrozenVector
{
    Q_OBJECT

public:
    using audios::FrozenVector::FrozenVector;
    ~Audios();

    void insert(int index, Audio *audio);
    void append(Audio *audio);
    void remove(int index);

    Audios::iterator insert(Audios::iterator before, Audio *audio);
    Audios::iterator erase(Audios::iterator position);

    int lowerBound(Audio *audio);

    audios::CurrentState *currentState();

    Audios &operator<<(Audio *audio);

public slots:
    void removeAudio(Audio *audio);

signals:
    void inserted(int index);
    void updated(int index);

private:
    QSet<Audio *> m_removed;
};

#endif // AUDIOS_HPP
