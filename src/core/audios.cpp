#include "audios.hpp"

Audios::Audios(QObject *parent)
    : Audios(Audio::vector(), parent)
{

}

Audios::Audios(const Audio::vector &vector, QObject *parent)
    : QObject(parent)
    , Audio::vector(vector)
    , m_state(false)
{

}

Audios::~Audios()
{
    if (!ownsObjects())
        return;

    for (Audio *audio : *this)
        delete audio;
}

Audio::vector Audios::vector() const
{
    return static_cast<Audio::vector>(*this);
}

bool Audios::ownsObjects() const
{
    return !m_state;
}

void Audios::insert(int index, Audio *audio)
{
    Audio::vector::insert(index, audio);
    emit inserted(index);
}

void Audios::append(Audio *audio)
{
    Audio::vector::append(audio);
    emit inserted(size() - 1);
}

void Audios::remove(int index)
{
    Audio *audio = at(index);
    Audio::vector::remove(index);
    emit removed(index);
    emit removedAudio(audio);
    delete audio;
}

Audios::iterator Audios::insert(Audios::iterator before, Audio *audio)
{
    auto position = Audio::vector::insert(before, audio);
    emit inserted(static_cast<int>(position - begin()));

    return position;
}

Audios::iterator Audios::erase(Audios::iterator position)
{
    auto next = Audio::vector::erase(position);
    emit removed(static_cast<int>(position - begin()));
    emit removedAudio(*position);
    delete *position;

    return next;
}

int Audios::lowerBound(Audio *audio)
{
    int low = 0;
    int high = size();
    while (low < high)
    {
        const int mid = (low + high) / 2;
        const int cmp = audio->tag().title().compare(at(mid)->tag().title(), Qt::CaseInsensitive);
        if (cmp < 0)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}

Audios *Audios::currentState()
{
    Audios *state = new Audios(*this, this);
    state->setState(true);
    connect(this, &Audios::removedAudio, state, &Audios::removeAudio);

    return state;
}

Audios &Audios::operator<<(Audio *audio)
{
    append(audio);

    return *this;
}

void Audios::removeAudio(Audio *audio)
{
    const int index = indexOf(audio);
    if (index != -1)
        remove(index);
}
